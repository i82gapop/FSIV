#include "test_data.hpp"

std::vector<std::string> tests_images = {
    "../data/logitech_000_000.png",
    "../data/logitech_000_001.png",
    "../data/logitech_000_002.png",
    "../data/logitech_000_003.png",
    "../data/logitech_000_004.png",
    "../data/logitech_000_005.png",
    "../data/logitech_000_006.png",
    "../data/logitech_000_007.png",
    "../data/logitech_000_008.png",
    "../data/logitech_000_009.png"
};

cv::Size test_board_size = cv::Size(5, 4);
float test_square_size = 0.03f;
cv::Size test_camera_size = cv::Size(640, 480);

const std::string tests_corners =
R"(%YAML:1.0
---
_2dpoints:
   - [ 2.04843552e+02, 1.07547348e+02, 2.73574219e+02, 1.04738823e+02,
       3.47419281e+02, 1.01647270e+02, 4.27942871e+02, 9.75626602e+01,
       5.16459778e+02, 9.35260773e+01, 1.97922363e+02, 1.81363754e+02,
       2.66457520e+02, 1.81355698e+02, 3.40605316e+02, 1.81171402e+02,
       4.21639404e+02, 1.80553528e+02, 5.11647797e+02, 1.80582916e+02,
       1.89470154e+02, 2.56733704e+02, 2.59008270e+02, 2.59782806e+02,
       3.33772614e+02, 2.63190918e+02, 4.16119141e+02, 2.66819153e+02,
       5.07141602e+02, 2.71166534e+02, 1.79922699e+02, 3.34417358e+02,
       2.51364258e+02, 3.40675598e+02, 3.27670868e+02, 3.47891846e+02,
       4.11103516e+02, 3.55654022e+02, 5.03240448e+02, 3.64691101e+02 ]
   - [ 1.59794174e+02, 8.21905136e+01, 2.35084564e+02, 8.14722214e+01,
       3.11987976e+02, 8.04155045e+01, 3.91390808e+02, 7.84760208e+01,
       4.73548767e+02, 7.70016251e+01, 1.50145248e+02, 1.52057053e+02,
       2.27366379e+02, 1.51687668e+02, 3.06690063e+02, 1.51299622e+02,
       3.88922607e+02, 1.50181717e+02, 4.74291626e+02, 1.50155060e+02,
       1.38532669e+02, 2.26239120e+02, 2.18887787e+02, 2.27299057e+02,
       3.01106964e+02, 2.27757370e+02, 3.86528992e+02, 2.28617584e+02,
       4.75190125e+02, 2.29926682e+02, 1.25389183e+02, 3.06077667e+02,
       2.09742233e+02, 3.08683563e+02, 2.95473999e+02, 3.11239349e+02,
       3.84213593e+02, 3.13913635e+02, 4.76337433e+02, 3.16876953e+02 ]
   - [ 1.26081047e+02, 9.55621262e+01, 2.07491486e+02, 1.10869972e+02,
       2.81824951e+02, 1.24468460e+02, 3.50563263e+02, 1.36367935e+02,
       4.13930237e+02, 1.48094315e+02, 1.20710030e+02, 1.71022400e+02,
       2.05829117e+02, 1.82667191e+02, 2.83295959e+02, 1.93168518e+02,
       3.54965546e+02, 2.02532944e+02, 4.20207733e+02, 2.12109863e+02,
       1.14927116e+02, 2.51920700e+02, 2.03783188e+02, 2.60511261e+02,
       2.84771484e+02, 2.67914795e+02, 3.58757385e+02, 2.74992828e+02,
       4.26582306e+02, 2.81803986e+02, 1.08313103e+02, 3.40599518e+02,
       2.01354813e+02, 3.45465393e+02, 2.85464203e+02, 3.49759613e+02,
       3.61893921e+02, 3.53882812e+02, 4.32389313e+02, 3.57668701e+02 ]
   - [ 1.44264420e+02, 1.55812790e+02, 2.06464981e+02, 1.61541412e+02,
       2.68014008e+02, 1.67293732e+02, 3.28868622e+02, 1.72518600e+02,
       3.89312714e+02, 1.77991882e+02, 1.38081207e+02, 2.17135849e+02,
       2.00523560e+02, 2.22474045e+02, 2.62294464e+02, 2.27739212e+02,
       3.23782318e+02, 2.33070770e+02, 3.84703339e+02, 2.38413864e+02,
       1.31180023e+02, 2.79279236e+02, 1.94346069e+02, 2.84325378e+02,
       2.56507996e+02, 2.89507446e+02, 3.18462799e+02, 2.94658051e+02,
       3.79964600e+02, 2.99954742e+02, 1.23753487e+02, 3.42470337e+02,
       1.87894531e+02, 3.47149384e+02, 2.50710297e+02, 3.52055817e+02,
       3.13032166e+02, 3.56950226e+02, 3.74938385e+02, 3.62102844e+02 ]
   - [ 2.13560379e+02, 1.13053970e+02, 2.74262360e+02, 1.12936005e+02,
       3.36505188e+02, 1.12996292e+02, 4.01006195e+02, 1.12770035e+02,
       4.67754395e+02, 1.12348717e+02, 2.20324310e+02, 1.72152893e+02,
       2.78484009e+02, 1.73202759e+02, 3.38510651e+02, 1.74185562e+02,
       4.00517181e+02, 1.75475967e+02, 4.65088806e+02, 1.75880615e+02,
       2.26199509e+02, 2.27624817e+02, 2.82562286e+02, 2.29161362e+02,
       3.40401276e+02, 2.31437134e+02, 4.00404846e+02, 2.33323517e+02,
       4.62514038e+02, 2.34889877e+02, 2.31176270e+02, 2.79813599e+02,
       2.86331299e+02, 2.81461151e+02, 3.42473785e+02, 2.83717010e+02,
       4.00457642e+02, 2.86194427e+02, 4.60350861e+02, 2.88734314e+02 ]
   - [ 1.82813110e+02, 1.62180298e+02, 2.31828888e+02, 1.58967224e+02,
       2.83903412e+02, 1.55976212e+02, 3.39566467e+02, 1.52534256e+02,
       4.00026367e+02, 1.48612259e+02, 1.95796204e+02, 2.15322968e+02,
       2.43334061e+02, 2.14438171e+02, 2.94016907e+02, 2.13358459e+02,
       3.48212402e+02, 2.12456635e+02, 4.07195923e+02, 2.10746109e+02,
       2.07177078e+02, 2.66301178e+02, 2.53980148e+02, 2.66586578e+02,
       3.03414612e+02, 2.67828094e+02, 3.56790039e+02, 2.68489929e+02,
       4.14335144e+02, 2.69149963e+02, 2.17499359e+02, 3.14741547e+02,
       2.64280212e+02, 3.16307190e+02, 3.13247742e+02, 3.18395416e+02,
       3.65538727e+02, 3.20537201e+02, 4.21572113e+02, 3.23114410e+02 ]
   - [ 2.05332245e+02, 1.23494110e+02, 2.67350311e+02, 1.36240295e+02,
       3.26192688e+02, 1.48324661e+02, 3.82535950e+02, 1.59972504e+02,
       4.36358734e+02, 1.70707230e+02, 1.93530258e+02, 1.82952911e+02,
       2.53862518e+02, 1.94269379e+02, 3.11489502e+02, 2.04777588e+02,
       3.66760803e+02, 2.15236740e+02, 4.19425110e+02, 2.24500290e+02,
       1.82257416e+02, 2.39746933e+02, 2.41162598e+02, 2.48850861e+02,
       2.97544403e+02, 2.58483765e+02, 3.51545380e+02, 2.67036865e+02,
       4.02951935e+02, 2.75196289e+02, 1.71294678e+02, 2.93494202e+02,
       2.29062057e+02, 3.00629761e+02, 2.83998810e+02, 3.08192871e+02,
       3.36620239e+02, 3.15350739e+02, 3.87253082e+02, 3.22486572e+02 ]
   - [ 1.64230759e+02, 8.61539230e+01, 2.41329773e+02, 8.50157547e+01,
       3.18315216e+02, 8.32768250e+01, 3.95886749e+02, 8.05839920e+01,
       4.74562561e+02, 7.86776962e+01, 1.52278976e+02, 1.38213638e+02,
       2.34818222e+02, 1.36149887e+02, 3.17538116e+02, 1.33718399e+02,
       4.01278900e+02, 1.30389603e+02, 4.85984131e+02, 1.28872803e+02,
       1.37591232e+02, 1.97028397e+02, 2.27176102e+02, 1.95506271e+02,
       3.16670776e+02, 1.92565201e+02, 4.07388763e+02, 1.90421371e+02,
       4.99344818e+02, 1.88853958e+02, 1.19663948e+02, 2.65829041e+02,
       2.18141449e+02, 2.65653290e+02, 3.15803558e+02, 2.64398621e+02,
       4.14503357e+02, 2.63282074e+02, 5.14734253e+02, 2.61722046e+02 ]
   - [ 2.22605896e+02, 7.81177063e+01, 2.89639313e+02, 7.65363846e+01,
       3.62216858e+02, 7.42039108e+01, 4.41507751e+02, 7.07288589e+01,
       5.29273560e+02, 6.81738129e+01, 1.96617966e+02, 1.33014420e+02,
       2.66022858e+02, 1.32838898e+02, 3.41628876e+02, 1.32396164e+02,
       4.24859406e+02, 1.31161621e+02, 5.18124634e+02, 1.31577423e+02,
       1.66502853e+02, 1.92815399e+02, 2.39355408e+02, 1.96129303e+02,
       3.18324799e+02, 1.98295044e+02, 4.06335388e+02, 2.01550552e+02,
       5.04820496e+02, 2.05811401e+02, 1.31614578e+02, 2.60125519e+02,
       2.08997543e+02, 2.67809784e+02, 2.92749359e+02, 2.75421478e+02,
       3.85993195e+02, 2.84120850e+02, 4.90429565e+02, 2.93522217e+02 ]
   - [ 1.43032532e+02, 9.36933212e+01, 2.23629578e+02, 1.11298874e+02,
       2.96278168e+02, 1.26536346e+02, 3.62893341e+02, 1.39781311e+02,
       4.23600250e+02, 1.52596161e+02, 1.44418793e+02, 1.56533707e+02,
       2.30352356e+02, 1.71025406e+02, 3.07647064e+02, 1.83653275e+02,
       3.78335083e+02, 1.94665436e+02, 4.42067688e+02, 2.06316055e+02,
       1.46175919e+02, 2.27433640e+02, 2.37949081e+02, 2.39416153e+02,
       3.20571991e+02, 2.48990051e+02, 3.95061218e+02, 2.58491852e+02,
       4.62194366e+02, 2.67508423e+02, 1.48054993e+02, 3.09610107e+02,
       2.46579178e+02, 3.18747559e+02, 3.34203705e+02, 3.26102020e+02,
       4.12617401e+02, 3.32665283e+02, 4.83908203e+02, 3.38748108e+02 ]
_3dpoints:
   - [ 2.99999993e-02, 2.99999993e-02, 0., 5.99999987e-02,
       2.99999993e-02, 0., 8.99999961e-02, 2.99999993e-02, 0.,
       1.19999997e-01, 2.99999993e-02, 0., 1.49999991e-01,
       2.99999993e-02, 0., 2.99999993e-02, 5.99999987e-02, 0.,
       5.99999987e-02, 5.99999987e-02, 0., 8.99999961e-02,
       5.99999987e-02, 0., 1.19999997e-01, 5.99999987e-02, 0.,
       1.49999991e-01, 5.99999987e-02, 0., 2.99999993e-02,
       8.99999961e-02, 0., 5.99999987e-02, 8.99999961e-02, 0.,
       8.99999961e-02, 8.99999961e-02, 0., 1.19999997e-01,
       8.99999961e-02, 0., 1.49999991e-01, 8.99999961e-02, 0.,
       2.99999993e-02, 1.19999997e-01, 0., 5.99999987e-02,
       1.19999997e-01, 0., 8.99999961e-02, 1.19999997e-01, 0.,
       1.19999997e-01, 1.19999997e-01, 0., 1.49999991e-01,
       1.19999997e-01, 0. ]
   - [ 2.99999993e-02, 2.99999993e-02, 0., 5.99999987e-02,
       2.99999993e-02, 0., 8.99999961e-02, 2.99999993e-02, 0.,
       1.19999997e-01, 2.99999993e-02, 0., 1.49999991e-01,
       2.99999993e-02, 0., 2.99999993e-02, 5.99999987e-02, 0.,
       5.99999987e-02, 5.99999987e-02, 0., 8.99999961e-02,
       5.99999987e-02, 0., 1.19999997e-01, 5.99999987e-02, 0.,
       1.49999991e-01, 5.99999987e-02, 0., 2.99999993e-02,
       8.99999961e-02, 0., 5.99999987e-02, 8.99999961e-02, 0.,
       8.99999961e-02, 8.99999961e-02, 0., 1.19999997e-01,
       8.99999961e-02, 0., 1.49999991e-01, 8.99999961e-02, 0.,
       2.99999993e-02, 1.19999997e-01, 0., 5.99999987e-02,
       1.19999997e-01, 0., 8.99999961e-02, 1.19999997e-01, 0.,
       1.19999997e-01, 1.19999997e-01, 0., 1.49999991e-01,
       1.19999997e-01, 0. ]
   - [ 2.99999993e-02, 2.99999993e-02, 0., 5.99999987e-02,
       2.99999993e-02, 0., 8.99999961e-02, 2.99999993e-02, 0.,
       1.19999997e-01, 2.99999993e-02, 0., 1.49999991e-01,
       2.99999993e-02, 0., 2.99999993e-02, 5.99999987e-02, 0.,
       5.99999987e-02, 5.99999987e-02, 0., 8.99999961e-02,
       5.99999987e-02, 0., 1.19999997e-01, 5.99999987e-02, 0.,
       1.49999991e-01, 5.99999987e-02, 0., 2.99999993e-02,
       8.99999961e-02, 0., 5.99999987e-02, 8.99999961e-02, 0.,
       8.99999961e-02, 8.99999961e-02, 0., 1.19999997e-01,
       8.99999961e-02, 0., 1.49999991e-01, 8.99999961e-02, 0.,
       2.99999993e-02, 1.19999997e-01, 0., 5.99999987e-02,
       1.19999997e-01, 0., 8.99999961e-02, 1.19999997e-01, 0.,
       1.19999997e-01, 1.19999997e-01, 0., 1.49999991e-01,
       1.19999997e-01, 0. ]
   - [ 2.99999993e-02, 2.99999993e-02, 0., 5.99999987e-02,
       2.99999993e-02, 0., 8.99999961e-02, 2.99999993e-02, 0.,
       1.19999997e-01, 2.99999993e-02, 0., 1.49999991e-01,
       2.99999993e-02, 0., 2.99999993e-02, 5.99999987e-02, 0.,
       5.99999987e-02, 5.99999987e-02, 0., 8.99999961e-02,
       5.99999987e-02, 0., 1.19999997e-01, 5.99999987e-02, 0.,
       1.49999991e-01, 5.99999987e-02, 0., 2.99999993e-02,
       8.99999961e-02, 0., 5.99999987e-02, 8.99999961e-02, 0.,
       8.99999961e-02, 8.99999961e-02, 0., 1.19999997e-01,
       8.99999961e-02, 0., 1.49999991e-01, 8.99999961e-02, 0.,
       2.99999993e-02, 1.19999997e-01, 0., 5.99999987e-02,
       1.19999997e-01, 0., 8.99999961e-02, 1.19999997e-01, 0.,
       1.19999997e-01, 1.19999997e-01, 0., 1.49999991e-01,
       1.19999997e-01, 0. ]
   - [ 2.99999993e-02, 2.99999993e-02, 0., 5.99999987e-02,
       2.99999993e-02, 0., 8.99999961e-02, 2.99999993e-02, 0.,
       1.19999997e-01, 2.99999993e-02, 0., 1.49999991e-01,
       2.99999993e-02, 0., 2.99999993e-02, 5.99999987e-02, 0.,
       5.99999987e-02, 5.99999987e-02, 0., 8.99999961e-02,
       5.99999987e-02, 0., 1.19999997e-01, 5.99999987e-02, 0.,
       1.49999991e-01, 5.99999987e-02, 0., 2.99999993e-02,
       8.99999961e-02, 0., 5.99999987e-02, 8.99999961e-02, 0.,
       8.99999961e-02, 8.99999961e-02, 0., 1.19999997e-01,
       8.99999961e-02, 0., 1.49999991e-01, 8.99999961e-02, 0.,
       2.99999993e-02, 1.19999997e-01, 0., 5.99999987e-02,
       1.19999997e-01, 0., 8.99999961e-02, 1.19999997e-01, 0.,
       1.19999997e-01, 1.19999997e-01, 0., 1.49999991e-01,
       1.19999997e-01, 0. ]
   - [ 2.99999993e-02, 2.99999993e-02, 0., 5.99999987e-02,
       2.99999993e-02, 0., 8.99999961e-02, 2.99999993e-02, 0.,
       1.19999997e-01, 2.99999993e-02, 0., 1.49999991e-01,
       2.99999993e-02, 0., 2.99999993e-02, 5.99999987e-02, 0.,
       5.99999987e-02, 5.99999987e-02, 0., 8.99999961e-02,
       5.99999987e-02, 0., 1.19999997e-01, 5.99999987e-02, 0.,
       1.49999991e-01, 5.99999987e-02, 0., 2.99999993e-02,
       8.99999961e-02, 0., 5.99999987e-02, 8.99999961e-02, 0.,
       8.99999961e-02, 8.99999961e-02, 0., 1.19999997e-01,
       8.99999961e-02, 0., 1.49999991e-01, 8.99999961e-02, 0.,
       2.99999993e-02, 1.19999997e-01, 0., 5.99999987e-02,
       1.19999997e-01, 0., 8.99999961e-02, 1.19999997e-01, 0.,
       1.19999997e-01, 1.19999997e-01, 0., 1.49999991e-01,
       1.19999997e-01, 0. ]
   - [ 2.99999993e-02, 2.99999993e-02, 0., 5.99999987e-02,
       2.99999993e-02, 0., 8.99999961e-02, 2.99999993e-02, 0.,
       1.19999997e-01, 2.99999993e-02, 0., 1.49999991e-01,
       2.99999993e-02, 0., 2.99999993e-02, 5.99999987e-02, 0.,
       5.99999987e-02, 5.99999987e-02, 0., 8.99999961e-02,
       5.99999987e-02, 0., 1.19999997e-01, 5.99999987e-02, 0.,
       1.49999991e-01, 5.99999987e-02, 0., 2.99999993e-02,
       8.99999961e-02, 0., 5.99999987e-02, 8.99999961e-02, 0.,
       8.99999961e-02, 8.99999961e-02, 0., 1.19999997e-01,
       8.99999961e-02, 0., 1.49999991e-01, 8.99999961e-02, 0.,
       2.99999993e-02, 1.19999997e-01, 0., 5.99999987e-02,
       1.19999997e-01, 0., 8.99999961e-02, 1.19999997e-01, 0.,
       1.19999997e-01, 1.19999997e-01, 0., 1.49999991e-01,
       1.19999997e-01, 0. ]
   - [ 2.99999993e-02, 2.99999993e-02, 0., 5.99999987e-02,
       2.99999993e-02, 0., 8.99999961e-02, 2.99999993e-02, 0.,
       1.19999997e-01, 2.99999993e-02, 0., 1.49999991e-01,
       2.99999993e-02, 0., 2.99999993e-02, 5.99999987e-02, 0.,
       5.99999987e-02, 5.99999987e-02, 0., 8.99999961e-02,
       5.99999987e-02, 0., 1.19999997e-01, 5.99999987e-02, 0.,
       1.49999991e-01, 5.99999987e-02, 0., 2.99999993e-02,
       8.99999961e-02, 0., 5.99999987e-02, 8.99999961e-02, 0.,
       8.99999961e-02, 8.99999961e-02, 0., 1.19999997e-01,
       8.99999961e-02, 0., 1.49999991e-01, 8.99999961e-02, 0.,
       2.99999993e-02, 1.19999997e-01, 0., 5.99999987e-02,
       1.19999997e-01, 0., 8.99999961e-02, 1.19999997e-01, 0.,
       1.19999997e-01, 1.19999997e-01, 0., 1.49999991e-01,
       1.19999997e-01, 0. ]
   - [ 2.99999993e-02, 2.99999993e-02, 0., 5.99999987e-02,
       2.99999993e-02, 0., 8.99999961e-02, 2.99999993e-02, 0.,
       1.19999997e-01, 2.99999993e-02, 0., 1.49999991e-01,
       2.99999993e-02, 0., 2.99999993e-02, 5.99999987e-02, 0.,
       5.99999987e-02, 5.99999987e-02, 0., 8.99999961e-02,
       5.99999987e-02, 0., 1.19999997e-01, 5.99999987e-02, 0.,
       1.49999991e-01, 5.99999987e-02, 0., 2.99999993e-02,
       8.99999961e-02, 0., 5.99999987e-02, 8.99999961e-02, 0.,
       8.99999961e-02, 8.99999961e-02, 0., 1.19999997e-01,
       8.99999961e-02, 0., 1.49999991e-01, 8.99999961e-02, 0.,
       2.99999993e-02, 1.19999997e-01, 0., 5.99999987e-02,
       1.19999997e-01, 0., 8.99999961e-02, 1.19999997e-01, 0.,
       1.19999997e-01, 1.19999997e-01, 0., 1.49999991e-01,
       1.19999997e-01, 0. ]
   - [ 2.99999993e-02, 2.99999993e-02, 0., 5.99999987e-02,
       2.99999993e-02, 0., 8.99999961e-02, 2.99999993e-02, 0.,
       1.19999997e-01, 2.99999993e-02, 0., 1.49999991e-01,
       2.99999993e-02, 0., 2.99999993e-02, 5.99999987e-02, 0.,
       5.99999987e-02, 5.99999987e-02, 0., 8.99999961e-02,
       5.99999987e-02, 0., 1.19999997e-01, 5.99999987e-02, 0.,
       1.49999991e-01, 5.99999987e-02, 0., 2.99999993e-02,
       8.99999961e-02, 0., 5.99999987e-02, 8.99999961e-02, 0.,
       8.99999961e-02, 8.99999961e-02, 0., 1.19999997e-01,
       8.99999961e-02, 0., 1.49999991e-01, 8.99999961e-02, 0.,
       2.99999993e-02, 1.19999997e-01, 0., 5.99999987e-02,
       1.19999997e-01, 0., 8.99999961e-02, 1.19999997e-01, 0.,
       1.19999997e-01, 1.19999997e-01, 0., 1.49999991e-01,
       1.19999997e-01, 0. ]
camera_matrix: !!opencv-matrix
   rows: 3
   cols: 3
   dt: d
   data: [ 7.0060538151780679e+02, 0., 3.0061483153262486e+02, 0.,
       7.0196207379964835e+02, 2.4340315369874025e+02, 0., 0., 1. ]
dist_coeffs: !!opencv-matrix
   rows: 1
   cols: 5
   dt: d
   data: [ -3.7454529519692394e-02, 1.5006130391843830e+00,
       2.8095163387273888e-03, -1.1201988193453340e-02,
       -6.2212487975776192e+00 ]
rvecs:
   - !!opencv-matrix
      rows: 3
      cols: 1
      dt: d
      data: [ -1.4357413074184289e-01, 3.9331821563531982e-01,
          6.1222663933307497e-02 ]
   - !!opencv-matrix
      rows: 3
      cols: 1
      dt: d
      data: [ -3.3738254161866943e-01, 1.6239391622361812e-01,
          4.3131562449832038e-02 ]
   - !!opencv-matrix
      rows: 3
      cols: 1
      dt: d
      data: [ -3.5225403287531626e-01, -3.6878246742420046e-01,
          4.2905910250075098e-02 ]
   - !!opencv-matrix
      rows: 3
      cols: 1
      dt: d
      data: [ -7.9795950509656502e-02, -1.4605836702757205e-02,
          8.6205278399545879e-02 ]
   - !!opencv-matrix
      rows: 3
      cols: 1
      dt: d
      data: [ 4.2698836925784150e-01, 2.0572083934766477e-01,
          -1.1574570958425304e-02 ]
   - !!opencv-matrix
      rows: 3
      cols: 1
      dt: d
      data: [ 3.7552258824280488e-01, 4.4782540127402981e-01,
          -8.9966679869926597e-02 ]
   - !!opencv-matrix
      rows: 3
      cols: 1
      dt: d
      data: [ 3.8642821506894309e-01, -2.1608695887923382e-01,
          2.0702421264205806e-01 ]
   - !!opencv-matrix
      rows: 3
      cols: 1
      dt: d
      data: [ -7.0755589479934822e-01, 6.5703492530852697e-02,
          5.3850790610893203e-03 ]
   - !!opencv-matrix
      rows: 3
      cols: 1
      dt: d
      data: [ -5.9947056143158661e-01, 3.9105648325058551e-01,
          1.9078322228713726e-01 ]
   - !!opencv-matrix
      rows: 3
      cols: 1
      dt: d
      data: [ -6.3354483563296227e-01, -4.2763751829853608e-01,
          -1.0490580855772204e-02 ]
tvecs:
   - !!opencv-matrix
      rows: 3
      cols: 1
      dt: d
      data: [ -6.3037803503657910e-02, -8.4750158766289274e-02,
          2.9653493923025431e-01 ]
   - !!opencv-matrix
      rows: 3
      cols: 1
      dt: d
      data: [ -8.2233708145126413e-02, -9.1659340247033455e-02,
          2.9109720592598182e-01 ]
   - !!opencv-matrix
      rows: 3
      cols: 1
      dt: d
      data: [ -9.1856534004753868e-02, -8.4805710650409996e-02,
          2.5690574575407410e-01 ]
   - !!opencv-matrix
      rows: 3
      cols: 1
      dt: d
      data: [ -1.0314475986933688e-01, -7.4980808581585595e-02,
          3.4512724705029030e-01 ]
   - !!opencv-matrix
      rows: 3
      cols: 1
      dt: d
      data: [ -7.2839576925324015e-02, -9.1056523562447672e-02,
          3.3268799797614224e-01 ]
   - !!opencv-matrix
      rows: 3
      cols: 1
      dt: d
      data: [ -9.4169525812339686e-02, -7.0693540536104799e-02,
          3.7599891118915169e-01 ]
   - !!opencv-matrix
      rows: 3
      cols: 1
      dt: d
      data: [ -6.6073714492943650e-02, -8.8119481071493685e-02,
          3.1181797411790435e-01 ]
   - !!opencv-matrix
      rows: 3
      cols: 1
      dt: d
      data: [ -8.1964897492826927e-02, -8.3460692652646037e-02,
          2.9657732627024441e-01 ]
   - !!opencv-matrix
      rows: 3
      cols: 1
      dt: d
      data: [ -5.0140326605631856e-02, -9.3204004082059866e-02,
          3.1368599737395114e-01 ]
   - !!opencv-matrix
      rows: 3
      cols: 1
      dt: d
      data: [ -8.7815647621114060e-02, -8.1408516568421380e-02,
          2.5912206233513824e-01 ]
)";