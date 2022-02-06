/*!
  Esto es un esqueleto de programa para usar en las prácticas
  de Visión Artificial.

  Se supone que se utilizará OpenCV.

  Para compilar, puedes ejecutar:
    g++ -Wall -o esqueleto esqueleto.cc `pkg-config opencv --cflags --libs`

*/

#include <iostream>
#include <exception>
#include <vector>

//Includes para OpenCV, Descomentar según los módulo utilizados.
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>

#include "dataset.hpp"
#include "features.hpp"
#include "debug.hpp"

#ifndef NDEBUG
int __Debug_Level = 0;
#endif

const cv::String keys =
    "{help h usage ? |      | print this message   }"
    "{f              |0     | Feature to extract. Default 0 is gray levels.}"
    "{f_params       |      | Feature parameters. Format <value>:<value>:<value>... }"
    "{class          |0     | Classifier to train. 0: K-NN, 1:SVM, 2:RTREES.}"
    "{@dataset       |<none>| Dataset pathname.}"
    "{@model         |<none>| Model filename.}"
    "{@image         |<none>| Input image.}"
#ifndef NDEBUG
    "{verbose        |0     | Set the verbose level.}"
#endif
    ;

int
main (int argc, char* const* argv)
{
  int retCode=EXIT_SUCCESS;

  try {

      cv::CommandLineParser parser(argc, argv, keys);
      parser.about("Test the traffic sign classifier on a input image.");
      if (parser.has("help"))
      {
          parser.printMessage();
          return 0;
      }

#ifndef NDEBUG
      __Debug_Level = parser.get<int>("verbose");
#endif

      FEATURE_ID feature_id = FEATURE_ID(parser.get<int>("f"));
      std::vector<float> feature_params;
      if (parser.has("f_params"))
      {
          std::istringstream in (parser.get<std::string>("f_params"));
          float v;
          while (in)
          {
              in >> v;
              if (in)
                  feature_params.push_back(v);
          }
      }

      std::string model_fname = parser.get<std::string>("@model");
      int classifier = parser.get<int>("class");
      cv::Mat input_img = cv::imread(parser.get<std::string>("@image"), cv::IMREAD_COLOR);
      if (input_img.empty())
      {
          std::cerr << "Error: could not read the input image '"
                    << parser.get<std::string>("@image") << "'." << std::endl;
          return EXIT_FAILURE;
      }
      if (!parser.check())
      {
          parser.printErrors();
          return 0;
      }

      cv::Size canonical_size(64, 64);

      std::vector<int> categories;
      std::vector<std::string> categories_names;
      if (! load_gtsrb_categories(parser.get<std::string>("@dataset"), categories, categories_names))
      {
          std::cerr << "Error: could not load the categories names from dataset."
                    << std::endl;
          return EXIT_FAILURE;
      }

      std::cout << "Loading classifier's model ... ";
      cv::Ptr<cv::ml::StatModel> clsf;
      if (classifier==0)
          //TODO: Load a KNearest model.
          clsf = cv::Algorithm::load<cv::ml::KNearest>(model_fname);
          //
      else if (classifier==1)
          //TODO: Load a SVM model.
          clsf = cv::Algorithm::load<cv::ml::SVM>(model_fname);
          //
      else if (classifier==2)
          //TODO: Load a RTrees model.
          clsf = cv::Algorithm::load<cv::ml::RTrees>(model_fname);
          //
      else
      {
          std::cerr << "Error: unknown classifier." << std::endl;
          return EXIT_FAILURE;
      }
      assert(clsf!=nullptr && clsf->isTrained());
      std::cout << " ok." << std::endl;

      bool go_out = false;
      while (! go_out)
      {
        cv::Rect roi = cv::selectROI("SELECT THE ROI", input_img);
        cv::destroyWindow("SELECT THE ROI");
        if (roi.area()==0)
            go_out = true;
        else
        {
            cv::Mat img;
            cv::resize(input_img(roi), img, canonical_size);

            cv::Mat desc;
            desc = fsiv_extract_feature(img, feature_id, feature_params);

            cv::Mat y_pred;

            //TODO: get the classifier prediction.
            clsf->predict(desc,y_pred);
            //
            assert(!y_pred.empty() && y_pred.rows==1);


            auto cat_it = std::find(categories.begin(), categories.end(),
                                    static_cast<size_t>(y_pred.at<float>(0)));
            std::string sign_name = "!!Unknown!!";
            if (cat_it != categories.end())
                    sign_name = categories_names[cat_it-categories.begin()];
            cv::Mat aux_img;
            input_img.copyTo(aux_img);
            cv::rectangle(aux_img, roi.tl(), roi.br(), cv::Scalar(0,255,0));
            cv::putText(aux_img, sign_name,
                        cv::Point(roi.x+1, roi.y+roi.height/2),
                        cv::FONT_HERSHEY_SIMPLEX, 1.0,
                        cv::Scalar(0,255,0),
                        3);

            cv::imshow("PREDICTION", aux_img);
            cv::waitKey(0);
            cv::destroyWindow("PREDICTION");
        }
      }
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception caught: " << e.what() << std::endl;
    retCode = EXIT_FAILURE;
  }
  return retCode;
}
