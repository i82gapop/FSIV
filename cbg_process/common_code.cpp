#include "common_code.hpp"

cv::Mat
convert_image_byte_to_float(const cv::Mat& img, cv::Mat& out)
{
    CV_Assert(img.depth()==CV_8U);
    //TODO

    img.convertTo(out, CV_32F, 1/255.0);

    //
    CV_Assert(out.rows==img.rows && out.cols==img.cols);
    CV_Assert(out.depth()==CV_32F);
    CV_Assert(img.channels()==out.channels());
    return out;
}

cv::Mat
convert_image_float_to_byte(const cv::Mat& img, cv::Mat& out)
{
    CV_Assert(img.depth()==CV_32F);
    //TODO

    img.convertTo(out, CV_8U, 255);

    //
    CV_Assert(out.rows==img.rows && out.cols==img.cols);
    CV_Assert(out.depth()==CV_8U);
    CV_Assert(img.channels()==out.channels());
    return out;
}

cv::Mat
convert_bgr_to_hsv(const cv::Mat& img, cv::Mat& out)
{
    CV_Assert(img.channels()==3);
    //TODO

    cv::cvtColor(img, out, cv::COLOR_BGR2HSV);

    //
    CV_Assert(out.channels()==3);
    return out;
}

cv::Mat
convert_hsv_to_bgr(const cv::Mat& img, cv::Mat& out)
{
    CV_Assert(img.channels()==3);
    //TODO

    cv::cvtColor(img, out, cv::COLOR_HSV2BGR);

    //
    CV_Assert(out.channels()==3);
    return out;
}

cv::Mat
cbg_process (const cv::Mat & in, cv::Mat& out,
             double contrast, double brightness, double gamma,
             bool only_luma)
{
    CV_Assert(in.depth()==CV_8U);
    //TODO
    //Recuerda: es recomendable trabajar en flotante [0,1]
    //Después deshacer el cambio a byte [0,255]

    cv::Mat inf;
    convert_image_byte_to_float(in, inf);

    if(only_luma&&in.channels()==3){

        cv::Mat hsv = inf.clone();
        convert_bgr_to_hsv(inf, hsv);

        std::vector<cv::Mat> channels;
        cv::split(hsv, channels);

        cv::pow(channels[2], gamma, channels[2]);

        channels[2] = (contrast * channels[2]);
        channels[2] += brightness;

        cv::merge(channels, hsv);

        convert_hsv_to_bgr(hsv, inf);
    }

    else{

        std::vector<cv::Mat> channels;
        cv::split(inf, channels);

        for(size_t i = 0; i < channels.size(); i++){

            cv::pow(channels[i], gamma, channels[i]);
            channels[i] = (contrast * channels[i]) + brightness;
        }

        cv::merge(channels, inf);
    }

    convert_image_float_to_byte(inf, out);

    //
    CV_Assert(out.rows==in.rows && out.cols==in.cols);
    CV_Assert(out.depth()==CV_8U);
    CV_Assert(out.channels()==in.channels());
    return out;
}
