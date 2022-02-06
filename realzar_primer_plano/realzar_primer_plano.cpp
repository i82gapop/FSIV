/*!
  Esto es un esqueleto de programa para usar en las prácticas
  de Visión Artificial.

  Se supone que se utilizará OpenCV.

  Para compilar, puedes ejecutar:
    g++ -Wall -o esqueleto esqueleto.cc `pkg-config opencv --cflags --libs`

*/

#include <iostream>
#include <exception>
#include <sstream>

//Includes para OpenCV, Descomentar según los módulo utilizados.
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/calib3d/calib3d.hpp>

#include "common_code.hpp"

const cv::String keys =
    "{help h usage ? |      | Print this message}"
    "{r              | x,y,w,h | Use a rectangle (x,y, widht, height)}"
    "{c              | x,y,r | Use a circle (x,y,radius)}"
    "{p              | x1,y1,x2,y2,x3,y3 | Use a closed polygon x1,y1,x2,y2,x3,y3,...}"
    "{i              |     | Interactive mode.}"
    "{@input         | <none> | input image.}"
    "{@output        | <none> | output image.}"
    ;

class Parametros{

public:

    std::vector<cv::Point> points;
    cv::Point point;
};

/*std::vector<cv::Point> points;
cv::Point point;*/

void trackbar_callback(int shape, void*)
{
    std::cout << "Opcion marcada: " << shape << " (Pulse intro para continuar o bien seleccione otra opción)" << std::endl;
}

void mouse_callback(int event, int x, int y, int flags, void* parametros)
{
    Parametros * aux = (Parametros *)parametros;

    if( event == cv::EVENT_LBUTTONDOWN ){

        aux->points.clear();

        aux->point = cv::Point(x, y);
        aux->points.push_back(aux->point);

        std::cout << "X,Y:" << x << "," << y << std::endl;
    }

    if( event == cv::EVENT_LBUTTONUP ){

        aux->point = cv::Point(x, y);
        aux->points.push_back(aux->point);

        std::cout << "X,Y:" << x << "," << y << std::endl;
    }
}

void mouse_callbackpoligono(int event, int x, int y, int flags, void* parametros)
{
    Parametros * aux = (Parametros *)parametros;

    if( event == cv::EVENT_LBUTTONDOWN ){

        aux->point = cv::Point(x, y);
        aux->points.push_back(aux->point);

        std::cout << "X,Y:" << x << "," << y << std::endl;
    }
}

int
main (int argc, char* const* argv)
{
    int retCode=EXIT_SUCCESS;

    try {
        cv::CommandLineParser parser(argc, argv, keys);
        parser.about("Do a foreground enhance using a ROI.");
        if (parser.has("help"))
        {
            parser.printMessage();
            return EXIT_SUCCESS;
        }

        cv::String input_n = parser.get<cv::String>("@input");
        cv::String output_n = parser.get<cv::String>("@output");
        if (!parser.check())
        {
            parser.printErrors();
            return EXIT_FAILURE;
        }

        cv::Mat in = cv::imread(input_n, cv::IMREAD_UNCHANGED);
        if (in.empty())
        {
            std::cerr << "Error: could not open input image '" << input_n
                      << "'." << std::endl;
            return EXIT_FAILURE;
        }
        cv::Mat mask = in.clone();
        cv::Mat out = in.clone();

        //TODO

        if (parser.has("i"))
        {
            Parametros parametros;

            std::cout << "Interactivo." << std::endl;

            int shape = 0;

            cv::namedWindow("EDITOR", cv::WINDOW_GUI_EXPANDED);

            cv::createTrackbar("funcionalidad", "EDITOR", &shape, 2, trackbar_callback);
            std::cout << "Opciones: " << std::endl;
            std::cout << "0. Rectangulo. " << std::endl;
            std::cout << "1. Circulo. " << std::endl;
            std::cout << "2. Polígono. " << std::endl;
            std::cout << "Opcion marcada: " << shape << " (Pulse intro para continuar o bien seleccione otra opción)" << std::endl;
            cv::imshow("EDITOR", in);


            int k = cv::waitKey(0)&0xff;
            if (k!=27){

                if(shape == 0){

                    std::cout << "Opcion elegida: " << shape << " (Pulse y arrastre para generar el rectangulo y una vez haya terminado pulse la tecla intro.)" << std::endl;
                    cv::setMouseCallback("EDITOR", mouse_callback, &parametros);
                    int width, height;

                    int k = cv::waitKey(0)&0xff;
                    if (k!=27){

                        width = parametros.points[parametros.points.size()-1].x - parametros.points[parametros.points.size()-2].x;
                        height = parametros.points[parametros.points.size()-1].y - parametros.points[parametros.points.size()-2].y;

                        cv::Mat ing = in.clone();

                        ing = convert_rgb_to_gray(ing);
                        ing = convert_gray_to_rgb(ing);

                        if(width < 0 && height < 0){

                            mask = generate_rectagle_mask(in.cols, in.rows, parametros.points[parametros.points.size()-1].x, parametros.points[parametros.points.size()-1].y, -width, -height, in.type());
                        }

                        else if(width < 0 && height >= 0 ){

                            mask = generate_rectagle_mask(in.cols, in.rows, parametros.points[parametros.points.size()-1].x, parametros.points[parametros.points.size()-2].y, -width, height, in.type());
                        }

                        else if(width >= 0 && height < 0){

                            mask = generate_rectagle_mask(in.cols, in.rows, parametros.points[parametros.points.size()-2].x, parametros.points[parametros.points.size()-1].y, width, -height, in.type());
                        }

                        else{

                            mask = generate_rectagle_mask(in.cols, in.rows, parametros.points[parametros.points.size()-2].x, parametros.points[parametros.points.size()-2].y, width, height, in.type());
                        }

                        out = combine_images(in, ing, mask);
                    }
                }

                else if (shape == 1){

                    std::cout << "Opcion elegida: " << shape << " (Pulse y arrastre para generar el circulo y una vez haya terminado pulse la tecla intro.)" << std::endl;
                    cv::setMouseCallback("EDITOR", mouse_callback, &parametros);
                    int radius, width, height;

                    int k = cv::waitKey(0)&0xff;
                    if (k!=27){

                        width = parametros.points[parametros.points.size()-1].x - parametros.points[parametros.points.size()-2].x;
                        height = parametros.points[parametros.points.size()-1].y - parametros.points[parametros.points.size()-2].y;

                        radius = sqrt(((width*width)+(height*height)));

                        cv::Mat ing = in.clone();

                        ing = convert_rgb_to_gray(ing);
                        ing = convert_gray_to_rgb(ing);

                        mask = generate_circle_mask(in.cols, in.rows, parametros.points[parametros.points.size()-2].x, parametros.points[parametros.points.size()-2].y, radius, in.type());

                        out = combine_images(in, ing, mask);
                    }
                }

                else if (shape == 2){

                    std::cout << "Opcion elegida: " << shape << " (Pulse para crear los puntos del poligono y una vez haya terminado pulse la tecla intro.)" << std::endl;
                    cv::setMouseCallback("EDITOR", mouse_callbackpoligono, &parametros);

                    int k = cv::waitKey(0)&0xff;
                    if (k!=27){

                        cv::Mat ing = in.clone();

                        ing = convert_rgb_to_gray(ing);
                        ing = convert_gray_to_rgb(ing);

                        mask = generate_polygon_mask(in.cols, in.rows, parametros.points, in.type());

                        out = combine_images(in, ing, mask);
                    }
                }
            }

            cv::destroyWindow("EDITOR");
        }

        else if (parser.get<cv::String>("r")!=("x,y,w,h")){

            std::cout << "Rectangulo." << std::endl;

            std::string s = parser.get<std::string>("r");

            std::vector<int> parametros;

            std::string delimiter = ",";
            size_t pos = 0;
            std::string token;

            while ((pos = s.find(",")) != std::string::npos) {
                token = s.substr(0, pos);

                parametros.push_back(atoi(token.c_str()));

                s.erase(0, pos + delimiter.length());
            }

            parametros.push_back(std::atoi(s.c_str()));

            if(parametros.size() == 4){

                cv::Mat ing = in.clone();

                ing = convert_rgb_to_gray(ing);
                ing = convert_gray_to_rgb(ing);

                mask = generate_rectagle_mask(in.cols, in.rows, parametros[0], parametros[1], parametros[2], parametros[3], in.type());

                out = combine_images(in, ing, mask);
            }

            else{

                std::cerr << "Numero de parametros de -r erroneo." << std::endl;

                return EXIT_FAILURE;
            }
        }

        else if (parser.get<cv::String>("c")!=("x,y,r")){


            std::cout << "Circulo." << std::endl;

            std::string s = parser.get<std::string>("c");

            std::vector<int> parametros;

            std::string delimiter = ",";
            size_t pos = 0;
            std::string token;

            while ((pos = s.find(",")) != std::string::npos) {
                token = s.substr(0, pos);

                parametros.push_back(atoi(token.c_str()));

                s.erase(0, pos + delimiter.length());
            }

            parametros.push_back(atoi(s.c_str()));

            if(parametros.size() == 3){

                cv::Mat ing = in.clone();

                ing = convert_rgb_to_gray(ing);
                ing = convert_gray_to_rgb(ing);

                mask = generate_circle_mask(in.cols, in.rows, parametros[0], parametros[1], parametros[2], in.type());

                out = combine_images(in, ing, mask);
            }

            else{

                std::cerr << "Numero de parametros de -c erroneo." << std::endl;

                return EXIT_FAILURE;
            }
        }


        else if (parser.get<cv::String>("p")!=("x1,y1,x2,y2,x3,y3")){

            std::cout << "Poligono." << std::endl;

            std::string s = parser.get<std::string>("p");

            std::vector<int> parametros;

            std::string delimiter = ",";
            size_t pos = 0;
            std::string token;

            while ((pos = s.find(",")) != std::string::npos) {
                token = s.substr(0, pos);

                parametros.push_back(atoi(token.c_str()));

                s.erase(0, pos + delimiter.length());
            }

            parametros.push_back(atoi(s.c_str()));

            if(parametros.size() >= 6 && parametros.size()%2==0){

                std::vector<cv::Point> points;

                for(size_t i = 0; i < parametros.size(); i+=2){

                    cv::Point point(parametros[i], parametros[i+1]);
                    points.push_back(point);
                }

                cv::Mat ing = in.clone();

                ing = convert_rgb_to_gray(ing);
                ing = convert_gray_to_rgb(ing);

                mask = generate_polygon_mask(in.cols, in.rows, points, in.type());

                out = combine_images(in, ing, mask);
            }

            else{

                std::cerr << "Numero de parametros de -p erroneo." << std::endl;

                return EXIT_FAILURE;
            }
        }
        //

        cv::namedWindow("INPUT", cv::WINDOW_GUI_EXPANDED);
        cv::imshow("INPUT", in);
        cv::namedWindow("MASK",  cv::WINDOW_GUI_EXPANDED);
        cv::imshow("MASK", mask);
        cv::namedWindow("OUTPUT",  cv::WINDOW_GUI_EXPANDED);
        cv::imshow("OUTPUT", out);

        int k = cv::waitKey(0)&0xff;
        if (k!=27)
            cv::imwrite(output_n, out);
    }
    catch (std::exception& e)
    {
        std::cerr << "Capturada excepcion: " << e.what() << std::endl;
        retCode = EXIT_FAILURE;
    }
    return retCode;
}
