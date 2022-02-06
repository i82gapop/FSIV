#include "common_code.hpp"

cv::Mat
convert_gray_to_rgb(const cv::Mat& img)
{
    CV_Assert(!img.empty());
    CV_Assert(img.channels()==1);
    cv::Mat out;

    //TODO
    cv::cvtColor(img, out, cv::COLOR_GRAY2BGR);
    //

    CV_Assert(out.channels()==3);
    CV_Assert(img.rows==out.rows && img.cols==out.cols);
    CV_Assert(img.depth()==out.depth());
    return out;
}

cv::Mat
convert_rgb_to_gray(const cv::Mat& img)
{
    CV_Assert(!img.empty());
    CV_Assert(img.channels()==3);
    cv::Mat out;
    //TODO
    cv::cvtColor(img, out, cv::COLOR_BGR2GRAY);
    //
    CV_Assert(out.channels()==1);
    CV_Assert(img.rows==out.rows && img.cols==out.cols);
    CV_Assert(img.depth()==out.depth());
    return out;
}

cv::Mat
generate_rectagle_mask(int img_width, int img_height,
                       int x, int y, int rect_width, int rect_height, int type)
{
    CV_Assert(img_width>0 && img_height>0);
    CV_Assert(x>=0 && x<img_width);
    CV_Assert(y>=0 && y<img_height);
    CV_Assert(rect_width>0 && rect_height>0);
    cv::Mat mask;
    //TODO

    mask = cv::Mat::zeros(img_height, img_width, type);
    cv::Point point1(x, y);
    cv::Point point2(x+rect_width, y+rect_height);
    const cv::Scalar color(255,255,255);
    int thickness = -1;

    cv::rectangle(mask, point1, point2, color, thickness);
    //
    CV_Assert(mask.rows==img_height && mask.cols==img_width);
    CV_Assert(mask.type()==type);
    return mask;
}

cv::Mat
generate_circle_mask(int img_width, int img_height,
                     int x, int y, int radius, int type)
{
    CV_Assert(img_width>0 && img_height>0);
    CV_Assert(x>=0 && x<img_width);
    CV_Assert(y>=0 && y<img_height);
    CV_Assert(radius > 0);
    cv::Mat mask;
    //TODO

    mask = cv::Mat::zeros(img_height, img_width, type);
    cv::Point center(x, y);
    const cv::Scalar color(255,255,255);
    int thickness = -1;

    cv::circle(mask, center, radius, color, thickness);

    //
    CV_Assert(mask.rows==img_height && mask.cols==img_width);
    CV_Assert(mask.type()==type);
    return mask;

}

cv::Mat
generate_polygon_mask(int img_width, int img_height,
                      std::vector<cv::Point>& points, int type)
{
    CV_Assert(img_width>0 && img_height>0);
    CV_Assert(points.size()>=3);
    cv::Mat mask;
    std::vector< std::vector<cv::Point> > polys;
    //TODO

    polys.push_back(points);

    mask = cv::Mat::zeros(img_height, img_width, type);
    const cv::Scalar color(255, 255, 255);

    cv::fillPoly(mask, polys, color, type);

    //
    CV_Assert(mask.rows==img_height && mask.cols==img_width);
    CV_Assert(mask.type()==type);
    return mask;
}

cv::Mat
combine_images(const cv::Mat& foreground, const cv::Mat& background,
               const cv::Mat& mask)
{
    CV_Assert(background.rows == foreground.rows &&
              background.cols==foreground.cols);
    CV_Assert(background.type()==foreground.type());
    CV_Assert(mask.rows == foreground.rows &&
              mask.cols==foreground.cols);
    CV_Assert(mask.type()==foreground.type());
    cv::Mat output;
    //TODO

    cv::Mat fusion1;
    cv::Mat fusion2;
    cv::Mat notfusion;
    cv::Mat fusion3;

    cv::bitwise_and(foreground, mask, fusion1);
    cv::bitwise_not(mask, notfusion);
    cv::bitwise_and(background, notfusion, fusion2);

    cv::bitwise_or(fusion1, fusion2, fusion3);
    output = fusion3;

    //
    CV_Assert(output.rows == foreground.rows && output.cols==foreground.cols);
    CV_Assert(output.type()==foreground.type());
    return output;
}
