#include <iostream>
#include "common_code.hpp"
#include <opencv2/imgproc.hpp>

cv::Mat
fsiv_create_gaussian_filter(const int r)
{
    CV_Assert(r>0);
    cv::Mat ret_v;
    //TODO: Remenber 6*sigma is approx 99,73% of the distribution.

    ret_v = cv::Mat::zeros((2*r+1), (2*r+1), CV_32FC1);

    float sigma = (2*r+1)/6.0;
    float exp;

    for(int i = -r; i <= r; i++){

        for(int j = -r; j <= r; j++){

            cv::Point point(r+i, r+j);
            exp = (pow(i,2) + pow(j,2));
            ret_v.at<float>(point) = std::exp(-(exp/(2*(pow(sigma, 2)))));
        }
    }

    float accum = static_cast<float>(cv::sum(ret_v)[0]);

    if(accum != 0){

        ret_v/= accum;
    }

    //
    CV_Assert(ret_v.type()==CV_32FC1);
    CV_Assert(ret_v.rows==(2*r+1) && ret_v.rows==ret_v.cols);
    CV_Assert(std::abs(1.0-cv::sum(ret_v)[0])<1.0e-6);
    return ret_v;
}

cv::Mat
fsiv_create_laplacian_filter(const int filter_type, int r1, int r2)
{
    CV_Assert(0<=filter_type && filter_type<=2);
    CV_Assert(0<r1 && r1<r2);
    cv::Mat filter;
    //TODO
    //Rember DoG = G[r2]-G[r1].

    if(filter_type==0){

        filter = cv::Mat::ones(3, 3, CV_32FC1);
        filter.at<float>(0,0) = 0;
        filter.at<float>(0,2) = 0;
        filter.at<float>(1,1) = -4;
        filter.at<float>(2,2) = 0;
        filter.at<float>(2,0) = 0;
    }

    else if(filter_type==1){

        filter = cv::Mat::ones(3, 3, CV_32FC1);
        filter.at<float>(1,1) = -8;
    }

    else{

        filter = cv::Mat::zeros((2*r2+1), (2*r2+1), CV_32FC1);

        cv::Mat g1 = fsiv_create_gaussian_filter(r1);
        cv::Mat g2 = fsiv_create_gaussian_filter(r2);

        cv::Size new_size (g2.cols, g2.rows);
        g1 = fsiv_extend_image(g1, new_size);

        filter = g2-g1;
    }

    //
    CV_Assert(filter.type()==CV_32FC1);
    CV_Assert((filter_type == 2) || (filter.rows==3 && filter.cols==3) );
    CV_Assert((filter_type != 2) || (filter.rows==(2*r2+1) &&
                                     filter.cols==(2*r2+1)));
    return filter;
}

cv::Mat
fsiv_fill_expansion(cv::Mat const& in, const int r)
{
    CV_Assert(!in.empty());
    CV_Assert(r>0);
    cv::Mat ret_v;
    //TODO:
    //Hint you don't need use any for sentence.

    if(in.type() == CV_32FC1){

        ret_v = cv::Mat::zeros(in.rows+2*r, in.cols+2*r, CV_32FC1);
    }

    else{

        ret_v = cv::Mat::zeros(in.rows+2*r, in.cols+2*r, CV_8UC1);
    }

    cv::Rect bounds(r, r, in.cols, in.rows);
    in.copyTo(ret_v(bounds));

    //
    CV_Assert(ret_v.type()==in.type());
    CV_Assert(ret_v.rows == in.rows+2*r);
    CV_Assert(ret_v.cols == in.cols+2*r);
    return ret_v;
}

cv::Mat
fsiv_circular_expansion(cv::Mat const& in, const int r)
{
    CV_Assert(!in.empty());
    CV_Assert(r>0);
    cv::Mat ret_v;
    //TODO
    //Hint you don't need use any for sentence.

    ret_v = cv::Mat(2*r+in.rows, 2*r+in.cols, in.type());
    in(cv::Rect(0, 0, r, r)).copyTo(ret_v(cv::Rect(in.cols+r, in.rows+r, r, r)));
    in(cv::Rect(0, 0, r, in.rows)).copyTo(ret_v(cv::Rect(in.cols+r, r, r, in.rows)));
    in(cv::Rect(0, 0, in.cols, r)).copyTo(ret_v(cv::Rect(r, in.rows+r, in.cols, r)));
    in(cv::Rect(0, in.rows-r, r, r)).copyTo(ret_v(cv::Rect(in.cols+r, 0, r, r)));
    in(cv::Rect(0, in.rows-r, in.cols, r)).copyTo(ret_v(cv::Rect(r, 0, in.cols, r)));
    in(cv::Rect(in.cols-r, 0, r, r)).copyTo(ret_v(cv::Rect(0, in.rows+r, r, r)));
    in(cv::Rect(in.cols-r, 0, r, in.rows)).copyTo(ret_v(cv::Rect(0, r, r, in.rows)));
    in(cv::Rect(in.cols-r, in.rows-r, r, r)).copyTo(ret_v(cv::Rect(0, 0, r, r)));

    in.copyTo(ret_v(cv::Rect(r, r, in.cols, in.rows)));

    //
    CV_Assert(ret_v.type()==in.type());
    CV_Assert(ret_v.rows == in.rows+2*r);
    CV_Assert(ret_v.cols == in.cols+2*r);
    CV_Assert(!(in.type()==CV_8UC1) || ret_v.at<uchar>(0,0)==in.at<uchar>(in.rows-r, in.cols-r));
    CV_Assert(!(in.type()==CV_8UC1) || ret_v.at<uchar>(0,ret_v.cols/2)==in.at<uchar>(in.rows-r, in.cols/2));
    CV_Assert(!(in.type()==CV_8UC1) || ret_v.at<uchar>(0,ret_v.cols-1)==in.at<uchar>(in.rows-r, r-1));
    CV_Assert(!(in.type()==CV_8UC1) || ret_v.at<uchar>(ret_v.rows/2,0)==in.at<uchar>(in.rows/2, in.cols-r));
    CV_Assert(!(in.type()==CV_8UC1) || ret_v.at<uchar>(ret_v.rows/2,ret_v.cols/2)==in.at<uchar>(in.rows/2, in.cols/2));
    CV_Assert(!(in.type()==CV_8UC1) || ret_v.at<uchar>(ret_v.rows-1,0)==in.at<uchar>(r-1, in.cols-r));
    CV_Assert(!(in.type()==CV_8UC1) || ret_v.at<uchar>(ret_v.rows-1,ret_v.cols/2)==in.at<uchar>(r-1, in.cols/2));
    CV_Assert(!(in.type()==CV_8UC1) || ret_v.at<uchar>(ret_v.rows-1,ret_v.cols-1)==in.at<uchar>(r-1, r-1));
    return ret_v;
}

cv::Mat
fsiv_filter2D(cv::Mat const& in, cv::Mat const& filter)
{
    CV_Assert(!in.empty() && !filter.empty());
    CV_Assert(in.type()==CV_32FC1 && filter.type()==CV_32FC1);
    cv::Mat ret_v;
    //TODO

    ret_v = cv::Mat(in.rows-2*(filter.rows/2), in.cols-2*(filter.cols/2), CV_32FC1);

    for(int i = 0; i < ret_v.rows; i++){

        for(int j = 0; j < ret_v.cols; j++){

            float accum = 0;

            for(int w = 0; w < filter.rows; w++){

                for(int z = 0; z < filter.rows; z++){

                    accum = accum + filter.at<float>(w, z) * in.at<float>(i + w, j + z);
                }
            }

            ret_v.at<float>(i, j) = accum;
        }
    }
    //
    CV_Assert(ret_v.type()==CV_32FC1);
    CV_Assert(ret_v.rows==in.rows-2*(filter.rows/2));
    CV_Assert(ret_v.cols==in.cols-2*(filter.cols/2));
    return ret_v;
}

cv::Mat
fsiv_extend_image(const cv::Mat& img, const cv::Size& new_size)
{
    CV_Assert(img.rows<new_size.height);
    CV_Assert(img.cols<new_size.width);
    cv::Mat out;
    //TODO(

    out = cv::Mat::zeros(new_size.height, new_size.width, img.type());
    cv::Rect bounds((new_size.height-img.rows)/2, (new_size.width-img.cols)/2, img.cols, img.rows);
    img.copyTo(out(bounds));

    //
    CV_Assert(out.type()==img.type());
    CV_Assert(out.rows == new_size.height);
    CV_Assert(out.cols == new_size.width);
    return out;
}

cv::Mat
fsiv_image_sharpening(const cv::Mat& in, float gain, int filter_type, bool only_luma,
                      int r1, int r2, bool circular)
{
    CV_Assert(in.depth()==CV_8U);
    CV_Assert(0<r1 && r1<r2);
    CV_Assert(0<=filter_type && filter_type<=2);
    cv::Mat out;
    //TODO

    cv::Mat filter = fsiv_create_laplacian_filter(filter_type, r1, r2);
    filter*= -1.0;
    filter.at<float>(filter.rows/2, filter.cols/2) += gain;

    if(in.channels() && only_luma){

        cv::Mat img;
        in.convertTo(img, CV_32F, 1/255.0);
        cv::cvtColor(img, img, cv::COLOR_BGR2HSV);
        std::vector <cv::Mat> channels;
        cv::split(img, channels);

        if(circular){

            channels[2] = fsiv_circular_expansion(channels[2] , filter.rows/2);
        }

        else{

            channels[2] = fsiv_fill_expansion(channels[2] , filter.rows/2);
        }

        channels[2] = fsiv_filter2D(channels[2], filter);
        cv::merge(channels, out);
        cv::cvtColor(out, out, cv::COLOR_HSV2BGR);
        out.convertTo(out, CV_8U, 255);  channels[2] = fsiv_circular_expansion(channels[2] , filter.rows/2);
    }

    else{

        if(in.channels()!=3){

            cv::Mat img;
            in.convertTo(img, CV_32F, 1/255.0);

            if(circular){

                img = fsiv_circular_expansion(img , filter.rows/2);
            }

            else{

                img = fsiv_fill_expansion(img , filter.rows/2);
            }

            img = fsiv_filter2D(img, filter);
            img.convertTo(img, CV_8U, 255);
            out = img.clone();
        }

        else{

            cv::Mat img;
            in.convertTo(img, CV_32F, 1/255.0);

            std::vector <cv::Mat> channels;
            cv::split(img, channels);

            for(int i = 0; i < channels.size(); i++){

                if(circular){

                    channels[i] = fsiv_circular_expansion(channels[i] , filter.rows/2);
                }

                else{

                    channels[i] = fsiv_fill_expansion(channels[i] , filter.rows/2);
                }
                channels[i] = fsiv_filter2D(channels[i], filter);
            }

            cv::merge(channels, out);
            out.convertTo(out, CV_8U, 255);
        }
    }


    //
    CV_Assert(out.type()==in.type());
    CV_Assert(out.rows==in.rows);
    CV_Assert(out.cols==in.cols);
    return out;
}
