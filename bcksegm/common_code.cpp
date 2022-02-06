// ----------------------------------------
// seglib.cpp
// (c) FSIV, University of Cordoba
// ----------------------------------------

#include "common_code.hpp"
#include <opencv2/imgproc.hpp>

void fsiv_remove_segmentation_noise(cv::Mat & img, int r)
{
    CV_Assert(img.type()==CV_8UC1);
    CV_Assert(r>0);
    //TODO
    //Apply a closing+opening using a square structuring element with radius r.

    cv::Mat structuringElement = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(r*2+1, r*2+1));

    cv::Mat dst;

    cv::morphologyEx(img, dst, cv::MORPH_CLOSE, structuringElement);
    cv::morphologyEx(dst, img, cv::MORPH_OPEN, structuringElement);

    //
}

void fsiv_segm_by_dif(const cv::Mat & prevFrame, const cv::Mat & curFrame,
                      cv::Mat & difimg, int thr, int r)
{
    CV_Assert(prevFrame.type()==CV_8UC3 && prevFrame.type()==curFrame.type());
    CV_Assert(prevFrame.size()==prevFrame.size());

    //TODO
    //Remenber: use >= to compare with 'thr'.

    cv::Mat previous, cursor;
    cv::cvtColor(prevFrame, previous, cv::COLOR_BGR2GRAY);
    cv::cvtColor(curFrame, cursor, cv::COLOR_BGR2GRAY);

    cv::Mat zeros = cv::Mat::zeros(prevFrame.size(), prevFrame.type());

    cv::absdiff(previous, cursor, zeros);
    difimg = zeros >= thr;

    if(r > 0){

        fsiv_remove_segmentation_noise(difimg, r);
    }

    //
    CV_Assert(difimg.type()==CV_8UC1);
    CV_Assert(difimg.size()==curFrame.size());
}

void fsiv_apply_mask(const cv::Mat & frame, const cv::Mat & mask,
                     cv::Mat & outframe)
{
    CV_Assert(frame.type()==CV_8UC1 || frame.type()==CV_8UC3);
    CV_Assert(mask.type()==CV_8UC1);
    CV_Assert(frame.size()==mask.size());

    //TODO
    //Remenber: frame could have 3 channels.

    cv::Mat masked;

    if(frame.channels()==3){

        masked = cv::Mat::zeros(frame.size(), CV_8UC1);
        cv::cvtColor(mask, masked, cv::COLOR_GRAY2BGR);
    }

    else{

        masked = mask;
    }

    outframe = frame & masked;

    //
    CV_Assert(outframe.type()==frame.type());
    CV_Assert(outframe.size()==frame.size());
}

bool
fsiv_learn_gaussian_model(cv::VideoCapture & input,
                          cv::Mat & mean,
                          cv::Mat & variance,
                          int num_frames,
                          int gauss_r,
                          const char * wname)
{
    CV_Assert(input.isOpened());
    bool was_ok = true;

    //TODO
    // Remenber you can compute the variance as:
    // varI = sum_n{I^2}/n - meanI²
    // Hint: convert to input frames to float [0,1].
    // Hint: use cv::accumulate() and cv::accumulateSquare().

    cv::Mat frame;
    int key=0, i=0, size=2*gauss_r+1;

    while(was_ok && key!=27 && i < num_frames){

        was_ok=input.read(frame);

        if(was_ok){

            frame.convertTo(frame, CV_32F, 1/255.0);

            if(gauss_r>0){

                cv::GaussianBlur(frame, frame, cv::Size(size, size), 0.0);
            }

            if(mean.empty() || variance.empty()){

                mean=frame.clone();
                variance=frame.mul(frame);
            }

            else{

                cv::accumulate(frame, mean);
                cv::accumulateSquare(frame, variance);
            }

            i++;

            if(wname){

                cv::imshow(wname, frame);

                //key=cv::waitKey(0)&0xff;
            }
        }
    }

    if(was_ok){

        mean = mean.mul(1.0/i);
        variance=variance.mul(1.0/i);
        variance = variance - mean.mul(mean);
    }

    //
    CV_Assert(!was_ok || mean.type()==CV_32FC3);
    CV_Assert(!was_ok || variance.type()==CV_32FC3);
    return was_ok;
}

void
fsiv_segm_by_gaussian_model(const cv::Mat & frame,
                            cv::Mat & mask,
                            const cv::Mat & mean,
                            const cv::Mat & variance, float k, int r)
{
    CV_Assert(frame.type()==CV_32FC3);

    //TODO
    //Remenber: a point belongs to the foreground (255) if |mean-I| >= k*stdev

    cv::Mat diff;
    cv::absdiff(frame, mean, diff);

    cv::Mat sqrt;
    cv::sqrt(variance, sqrt);
    sqrt*=k;

    cv::Mat masked = diff >= sqrt;

    std::vector<cv::Mat> vector;
    cv::split(masked, vector);

    cv::bitwise_or(vector[0], vector[1], mask);
    cv::bitwise_or(mask, vector[2], mask);

    if(r>0){

        fsiv_remove_segmentation_noise(mask, r);
    }

    //
    CV_Assert(mask.type()==CV_8UC1);
}

void
fsiv_update_gaussian_model(const cv::Mat & frame,
                           const cv::Mat & mask,
                           unsigned long frame_count,
                           cv::Mat & mean,
                           cv::Mat & variance,
                           float alpha,
                           unsigned short_term_update_period,
                           unsigned long_term_update_period)
{
    CV_Assert(frame.type()==CV_32FC3);
    CV_Assert(mask.type()==CV_8UC1);
    CV_Assert(mean.type()==CV_32FC3);
    CV_Assert(variance.type()==CV_32FC3);
    CV_Assert(frame.size()==mask.size());

    //TODO
    //Remember: In the short term updating you must update the model using
    //the background only (not mask).
    //However in the long term updating you must update
    //the model using both background and foreground (without mask).
    //Hint: a period is met when (idx % period) == 0
    //Hint: use accumulateWeighted to update the model.

    cv::Mat negative;
    cv::bitwise_not(mask, negative);

    if(short_term_update_period > 0 && frame_count % short_term_update_period == 0){

        cv::accumulateWeighted(frame, mean, alpha, negative);
        cv::accumulateWeighted(frame.mul(frame), variance, alpha, negative);
    }

    else if(long_term_update_period > 0 && frame_count % long_term_update_period == 0){

        cv::accumulateWeighted(frame, mean, alpha);
        cv::accumulateWeighted(frame.mul(frame), variance, alpha);
    }

    //
}
