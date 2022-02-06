#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "debug.hpp"
#include "dataset.hpp"
#include "features.hpp"
#include <opencv2/imgproc.hpp>


bool
load_gtsrb_categories(const std::string& dataset_pathname,
                      std::vector<int>& cats,
                      std::vector<std::string>& descs)
{
    bool ret_val = false;
    std::ifstream in(dataset_pathname+"/train/CLASSES.TXT");
    if (in)
    {
        int class_label = 0;
        char sep = ' ';
        std::string class_description;
        while(in)
        {
            in >> class_label >> sep >> sep >> sep >> class_description;
            if (in)
            {
                cats.push_back(class_label);
                descs.push_back(class_description);
            }
        }
        ret_val = true;
    }
    return ret_val;
}

bool
load_gtsrb_train_metadata(const std::string& metadata_file,
                          std::vector<std::string> & lfiles,
                          std::vector<cv::Rect>& rois,
                          cv::Mat & labels)
{
    bool ret_val = true;
    DEBUG(1, "Loading metadata from file '"<< metadata_file << "'." << std::endl);
    std::ifstream input (metadata_file);
    if (input)
    {
        std::vector<int> labels_v;
        std::istringstream line;
        std::string dataset_path;

        size_t pos = metadata_file.rfind("/");
        if (pos != std::string::npos)
            dataset_path=metadata_file.substr(0, pos);
        else
            dataset_path=".";
        DEBUG(2, "\tDataset path is: "<< dataset_path << "'." << std::endl);
        while(input && ret_val)
        {
            std::string buffer;
            //get a line.
            input >> buffer;
            if (input)
            {
                DEBUG(3,"\tDecoding line: '"<< buffer << "'."<< std::endl);
                //replace ; by ' '
                for(size_t i=0;i<buffer.size(); ++i)
                    if (buffer[i]==';')
                        buffer[i]=' ';
                //get the line's metadata.
                std::istringstream line (buffer);
                std::string filename;
                int w, h, x1, y1, x2, y2, label;
                line >> filename >> w >> h >> x1 >> y1 >> x2 >> y2 >> label;
                if (line)
                {
                    lfiles.push_back(dataset_path+'/'+filename);
                    rois.push_back(cv::Rect(x1, y1, x2-x1, y2-y1));
                    labels_v.push_back(label);
                    DEBUG(3,"\tDecoded fname: '" << lfiles.back() << "'." << std::endl);
                    DEBUG(3,"\tDecoded roi  :  " << rois.back() << std::endl);
                    DEBUG(3,"\tDecoded label:  " << labels_v.back() << std::endl);
                }
                else
                    ret_val = false;
            }
        }
        if (ret_val)
        {
            //Transform vector to cv::Mat.
            labels = cv::Mat(labels_v.size(), 1, CV_32SC1);
            std::copy(labels_v.begin(), labels_v.end(), labels.begin<int>());
        }
    }
    else
        ret_val = false;
    return ret_val;
}

bool
load_gtsrb_test_metadata(const std::string& dataset_path,
                          std::vector<std::string> & lfiles,
                          std::vector<cv::Rect>& rois,
                          cv::Mat & labels)
{
    bool ret_val = true;
    std::string metadata_file = dataset_path + "/test/metadada.csv";
    DEBUG(1, "Loading metadata from file '"<< metadata_file << "'."
          << std::endl);
    std::ifstream input (metadata_file);
    if (input)
    {
        std::vector<int> labels_v;
        std::istringstream line;
        while(input && ret_val)
        {
            std::string buffer;
            //get a line.
            input >> buffer;
            if (input)
            {
                DEBUG(3,"\tDecoding line: '"<< buffer << "'."<< std::endl);
                //replace ; by ' '
                for(size_t i=0;i<buffer.size(); ++i)
                    if (buffer[i]==';')
                        buffer[i]=' ';
                //get the line's metadata.
                std::istringstream line (buffer);
                std::string filename;
                int w, h, x1, y1, x2, y2, label;
                line >> filename >> w >> h >> x1 >> y1 >> x2 >> y2 >> label;
                if (line)
                {
                    lfiles.push_back(dataset_path+"/test/"+filename);
                    rois.push_back(cv::Rect(x1, y1, x2-x1, y2-y1));
                    labels_v.push_back(label);
                    DEBUG(3,"\tDecoded fname: '" << lfiles.back() << "'." << std::endl);
                    DEBUG(3,"\tDecoded roi  :  " << rois.back() << std::endl);
                    DEBUG(3,"\tDecoded label:  " << labels_v.back() << std::endl);
                }
                else
                    ret_val = false;
            }
        }
        if (ret_val)
        {
            //Transform vector to cv::Mat.
            labels = cv::Mat(labels_v.size(), 1, CV_32SC1);
            std::copy(labels_v.begin(), labels_v.end(), labels.begin<int>());
        }
    }
    else
        ret_val = false;
    return ret_val;
}

void
draw_histogram(cv::Mat const& h_,
               cv::Mat& img,
               cv::Scalar color)
{

    assert(!img.empty() && img.type()==CV_8UC3);
    assert(!h_.empty() && h_.type()==CV_32FC1);
    const int hist_w = img.cols;
    const int hist_h = img.rows;
    const int hist_size = std::max(h_.rows, h_.cols);
    const int bin_w = cvRound( (double) hist_w/hist_size );
    cv::Mat h;
    cv::normalize(h_, h, 0, hist_h, cv::NORM_MINMAX);
    DEBUG(3, "Drawing histogram. N bins=" << hist_size << " img binw= "
          << bin_w << std::endl  );
    for( int i = 1; i < hist_size; i++ )
    {
        cv::line(img, cv::Point( bin_w*(i-1), hist_h - cvRound(h.at<float>(i-1)) ),
              cv::Point( bin_w*(i), hist_h - cvRound(h.at<float>(i)) ),
              color, 2, 8, 0  );
    }
}

void
draw_histogram_descriptor(cv::Mat const& desc,
             cv::Mat & img,
             int ncells[],
             cv::Scalar color)
{
    DEBUG(1, "Drawing an histogram descriptor with grip shape RxC: " << ncells[0]
            << 'x' << ncells[1] << " on an image with size " << img.rows
            << 'x' << img.cols << std::endl);
    assert(!desc.empty() && desc.type()==CV_32FC1);
    assert(ncells[0]*ncells[1]>0);
    assert(desc.rows==1);
    assert((desc.cols%(ncells[0]*ncells[1])) == 0);
    assert(img.empty() || (img.type()==CV_8UC3 && img.cols > desc.cols/(ncells[0]*ncells[1])));
    const int n_cells = ncells[0]*ncells[1];
    const int h_size = desc.cols/n_cells;
    if (img.empty())
        img = cv::Mat::zeros(h_size*n_cells/2, h_size*n_cells, CV_8UC3);
    const int cell_height = cvRound((double)img.rows/ncells[0]);
    const int cell_width = cvRound((double)img.cols/ncells[1]);
    DEBUG(2, "Cells img size (WxH):" << cell_width << 'x' << cell_height
          << std::endl);
    DEBUG(2, "Hist size is " << h_size << std::endl);
    for (int row=0, i=0; row < ncells[0]; ++row)
        for (int col=0; col < ncells[1]; ++col, ++i)
        {
            DEBUG(3,"Draw desc interval " << cv::Rect(i*h_size, 0, h_size, 1)
                  << " in img cell " << cv::Rect(col*cell_width, row*cell_height,
                                                 cell_width, cell_height)
                  << std::endl);
            cv::Mat h = desc(cv::Rect(i*h_size, 0, h_size, 1));
            cv::Mat img_roi = img(cv::Rect(col*cell_width, row*cell_height,
                                           cell_width, cell_height));
            draw_histogram(h, img_roi, color);
        }
}

float
compute_file_size(std::string const& fname, const long units)
{
    float size = -1.0;
    std::ifstream file (fname);
    if (file)
    {
        file.seekg (0, file.end);
        long length = file.tellg();
        size = static_cast<float>(length) / static_cast<float>(units);
    }
    return size;
}
