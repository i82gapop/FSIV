#include <iostream>
#include "dataset.hpp"
#include "features.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "debug.hpp"

/**
 * @brief Extract gray levels features.
 * The values are float [0,1] normalized.
 * @param img
 * @return
 */
static
cv::Mat extract_gray_levels(const cv::Mat & img)
{
    CV_Assert(img.type()==CV_8UC3);
    cv::Mat feature;
    //TODO
    //Hint: convet to gray level normalized as float [0,1].
    //Hint: user mat::reshape() method to get a row descriptor.

    cv::cvtColor(img, feature,cv::COLOR_BGR2GRAY);
    feature.convertTo(feature,CV_32FC1,1/255.0);
    feature = feature.reshape(1, 1);

    //
    return feature;
}

//TODO
//Add code to extract other kind of features.
//Do not forget to add a new value to enum FEATURE_ID for each new feature and
// the a new switch's case into fsiv_extract_feature function.

static
cv::Mat convert_bgr_to_hsv(const cv::Mat& img)
{
    CV_Assert(img.type()==CV_8UC3);
    //TODO
    cv::Mat feature;
    std::vector<cv::Mat> mat;
    cvtColor(img, feature, CV_BGR2HSV);
    cv::split(feature,mat);
    mat[0].convertTo(mat[0], CV_32FC1, 1/255.0);
    feature = mat[0].reshape(1, 1);
    //
    return feature;
}

static
cv::Mat convert_bgr_to_ycrcb(const cv::Mat& img)
{
    CV_Assert(img.type()==CV_8UC3);
    //TODO
    cv::Mat feature;
    std::vector<cv::Mat> mat;
    cvtColor(img, feature, CV_BGR2YCrCb);
    cv::split(feature, mat);
    mat[0].convertTo(mat[0], CV_32FC1, 1/255.0);
    feature = mat[0].reshape(1, 1);
    //
    return feature;
}

//

cv::Mat
fsiv_extract_feature (const cv::Mat& img, FEATURE_ID feature_id,
                       const std::vector<float>& params)
{
    CV_Assert(img.type()==CV_8UC3);
    cv::Mat feature;
    switch (feature_id) {
    case FSIV_GREY_LEVELS:    {
        feature = extract_gray_levels(img);
        break;
    }
        //TODO
        //Añade aqui los 'case' de las funciones que implementes.
    case FSIV_HSV:{
        feature = convert_bgr_to_hsv(img);
        break;
    }

    case FSIV_YCRCB:{
        feature = convert_bgr_to_ycrcb(img);
        break;
    }

        //
    default: {
        std::cerr << "Error: unknown feature id: " << feature_id << std::endl;
    }
    }

    CV_Assert(feature.rows==1);
    CV_Assert(feature.type()==CV_32FC1);
    return feature;
}


bool
compute_features_from_list(const std::vector<std::string> & lfiles,
                           const std::vector<cv::Rect>& rois,
                           const cv::Size& canonical_size, cv::Mat &descs,
                           FEATURE_ID feature_id,
                           const std::vector<float>& feature_params)
{
    DEBUG(1, "Computing feature descriptors from files" << std::endl);
    bool ret_val = true;
    for (size_t i =0; i < lfiles.size() && ret_val; i++)
    {
        DEBUG(2, "\t Processing image: '" << lfiles[i] << "'." << std::endl);
        cv::Mat image = cv::imread(lfiles[i], cv::IMREAD_COLOR);
        if (!image.empty())
        {
#ifndef NDEBUG
            if (__Debug_Level>=3)
            {
                cv::imshow("IMAGE", image);
                cv::imshow("ROI", image(rois[i]));
            }
#endif
            cv::Mat canonical_img;
            cv::resize(image(rois[i]), canonical_img, canonical_size);
            cv::Mat descriptor;
            descriptor = fsiv_extract_feature(canonical_img, feature_id, feature_params);
            if (i==0)
            {
                descs = cv::Mat(lfiles.size(), descriptor.cols, CV_32FC1);
                descriptor.copyTo(descs.row(0));
            }
            else
                descriptor.copyTo(descs.row(i));
        }
        else
            ret_val = false;
    }
#ifndef NDEBUG
            if (__Debug_Level>=3)
                cv::destroyAllWindows();
#endif
    return ret_val;
}
