#pragma once
#include <vector>
#include <opencv2/core.hpp>

typedef enum {
    FSIV_GREY_LEVELS=0, // Use raw grey pixel grey levels.
    //Add new features to extract.
    FSIV_HSV=1,
    FSIV_YCRCB=2
} FEATURE_ID;

/**
 * @brief Extract features from an image.
 * @param img is the image where extracting features.
 * @param feature_id what feature to extract.
 * @param params is an array of parameters regarding the feature to extract.
 * @return the feature as row sample.
 * @post ret_v.rows==1
 */
cv::Mat fsiv_extract_feature (const cv::Mat& img, FEATURE_ID feature_id,
                         const std::vector<float>& params=std::vector<float>());


/**
 * @brief Compute the image descriptors for a set of images.
 * @param[in] lfiles are the filenames of the images.
 * @param[in] rois are the rois where the signs are.
 * @param[in] canonical_size is size to resize the input roi.
 * @param[in] feature_id is the feature to extract.
 * @param[in] feature_params is a vector with parameters regarding the feature to extract.
 * @param[out] descs the output descriptors, one row per image.
 * @return true if success.
 */
bool compute_features_from_list(const std::vector<std::string> & lfiles,
                                const std::vector<cv::Rect>& rois,
                                const cv::Size &canonical_size,
                                cv::Mat& descs,
                                FEATURE_ID feature_id=FSIV_GREY_LEVELS,
                                const std::vector<float> &feature_params = std::vector<float>());
