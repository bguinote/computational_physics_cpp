#include <stdio.h>
#include <stdlib.h>
#include <math.h>
FILE* raizes, * pesos;

/* Os dados abaixo poderiam ter sido implementados diretamente no programa de quadratura gaussiana,
mas fazendo dessa forma o programa de quadratura fica mais elegante e menor */

double x_k[20][20] = { {  0.e-16  },
{  -0.577350269189626, 0.577350269189626  },
{  -0.774596669241483, 0.e-16, 0.774596669241483  },
{  -0.861136311594053, -0.339981043584856, 0.339981043584856, 0.861136311594053  },
{  -0.906179845938664, -0.538469310105683, 0.e-16, 0.538469310105683, 0.906179845938664  },
{  -0.932469514203152, -0.661209386466265, -0.238619186083197, 0.238619186083197, 0.661209386466265, 0.932469514203152  },
{  -0.949107912342759, -0.74153118559939, -0.405845151377397, 0, 0.405845151377397, 0.74153118559939, 0.949107912342759  },
{  -0.96028985649754, -0.79666647741363, -0.525532409916329, -0.18343464249565, 0.18343464249565, 0.525532409916329, 0.79666647741363, 0.96028985649754  },
{  -0.96816023950763, -0.83603110732664, -0.61337143270059, -0.324253423403809, 0.e-16, 0.324253423403809, 0.61337143270059, 0.83603110732664, 0.96816023950763  },
{  -0.97390652851717, -0.86506336668898, -0.67940956829902, -0.433395394129247, -0.1488743389816312, 0.1488743389816312, 0.433395394129247, 0.67940956829902, 0.86506336668898, 0.97390652851717  },
{  -0.9782286581461, -0.8870625997681, -0.730152005574, -0.51909612920681, -0.269543155952345, 0.e-16, 0.269543155952345, 0.51909612920681, 0.730152005574, 0.8870625997681, 0.9782286581461  },
{  -0.9815606342467, -0.9041172563705, -0.7699026741943, -0.58731795428662, -0.36783149899818, -0.1252334085114689, 0.1252334085114689, 0.36783149899818, 0.58731795428662, 0.7699026741943, 0.9041172563705, 0.9815606342467  },
{  -0.9841830547186, -0.917598399223, -0.8015780907333, -0.6423493394403, -0.44849275103645, -0.230458315955135, 0.e-16, 0.230458315955135, 0.44849275103645, 0.6423493394403, 0.8015780907333, 0.917598399223, 0.9841830547186  },
{  -0.986283808697, -0.928434883664, -0.82720131507, -0.6872929048117, -0.51524863635815, -0.31911236892789, -0.1080549487073437, 0.1080549487073437, 0.31911236892789, 0.51524863635815, 0.6872929048117, 0.82720131507, 0.928434883664, 0.986283808697  },
{  -0.98799251802, -0.937273392401, -0.84820658341, -0.72441773136, -0.5709721726085, -0.39415134707756, -0.201194093997435, 0.e-16, 0.201194093997435, 0.39415134707756, 0.5709721726085, 0.72441773136, 0.84820658341, 0.937273392401, 0.98799251802  },
{  -0.989400934992, -0.94457502307, -0.865631202388, -0.755404408355, -0.6178762444026, -0.45801677765723, -0.281603550779259, -0.0950125098376374, 0.0950125098376374, 0.281603550779259, 0.45801677765723, 0.6178762444026, 0.755404408355, 0.865631202388, 0.94457502307, 0.989400934992  },
{  -0.99057547531, -0.95067552177, -0.88023915373, -0.781514003897, -0.657671159217, -0.5126905370865, -0.35123176345388, -0.178484181495848, 0.e-16, 0.178484181495848, 0.35123176345388, 0.5126905370865, 0.657671159217, 0.781514003897, 0.88023915373, 0.95067552177, 0.99057547531  },
{  -0.99156516842, -0.95582394957, -0.8926024665, -0.80370495897, -0.69168704306, -0.5597708310739, -0.41175116146284, -0.251886225691506, -0.0847750130417353, 0.0847750130417353, 0.251886225691506, 0.41175116146284, 0.5597708310739, 0.69168704306, 0.80370495897, 0.8926024665, 0.95582394957, 0.99156516842  },
{  -0.99240684384, -0.9602081521, -0.90315590361, -0.82271465654, -0.72096617734, -0.600545304662, -0.464570741376, -0.31656409996363, -0.160358645640225, 0.e-16, 0.160358645640225, 0.31656409996363, 0.464570741376, 0.600545304662, 0.72096617734, 0.82271465654, 0.90315590361, 0.9602081521, 0.99240684384  },
{  -0.9931285992, -0.9639719273, -0.9122344283, -0.8391169718, -0.74633190646, -0.636053680727, -0.5108670019508, -0.37370608871542, -0.227785851141645, -0.0765265211334973, 0.0765265211334973, 0.227785851141645, 0.37370608871542, 0.5108670019508, 0.636053680727, 0.74633190646, 0.8391169718, 0.9122344283, 0.9639719273, 0.9931285992  } };

double w_k[20][20] = { {  2.  },
{  1., 1.  },
{  0.555555555555556, 0.88888888888889, 0.555555555555556  },
{  0.347854845137454, 0.65214515486255, 0.65214515486255, 0.347854845137454  },
{  0.23692688505619, 0.47862867049937, 0.56888888888889, 0.47862867049937, 0.23692688505619  },
{  0.17132449237917, 0.36076157304814, 0.46791393457269, 0.46791393457269, 0.36076157304814, 0.17132449237917  },
{  0.12948496616887, 0.27970539148928, 0.3818300505051, 0.4179591836735, 0.3818300505051, 0.27970539148928, 0.12948496616887  },
{  0.10122853629038, 0.2223810344534, 0.3137066458779, 0.3626837833784, 0.3626837833784, 0.3137066458779, 0.2223810344534, 0.10122853629038  },
{  0.0812743883616, 0.1806481606949, 0.2606106964029, 0.31234707704, 0.3302393550013, 0.31234707704, 0.2606106964029, 0.1806481606949, 0.0812743883616  },
{  0.0666713443087, 0.1494513491506, 0.219086362516, 0.26926671931, 0.295524224715, 0.295524224715, 0.26926671931, 0.219086362516, 0.1494513491506, 0.0666713443087  },
{  0.0556685671162, 0.125580369465, 0.186290210928, 0.233193764592, 0.26280454451, 0.272925086778, 0.26280454451, 0.233193764592, 0.186290210928, 0.125580369465, 0.0556685671162  },
{  0.047175336387, 0.106939325995, 0.160078328543, 0.203167426723, 0.233492536538, 0.249147045813, 0.249147045813, 0.233492536538, 0.203167426723, 0.160078328543, 0.106939325995, 0.047175336387  },
{  0.040484004765, 0.092121499838, 0.13887351022, 0.17814598076, 0.20781604754, 0.22628318026, 0.23255155323, 0.22628318026, 0.20781604754, 0.17814598076, 0.13887351022, 0.092121499838, 0.040484004765  },
{  0.035119460332, 0.08015808716, 0.12151857069, 0.15720316716, 0.18553839748, 0.20519846372, 0.21526385346, 0.21526385346, 0.20519846372, 0.18553839748, 0.15720316716, 0.12151857069, 0.08015808716, 0.035119460332  },
{  0.030753242, 0.07036604749, 0.10715922047, 0.13957067793, 0.16626920582, 0.18616100002, 0.19843148533, 0.20257824193, 0.19843148533, 0.18616100002, 0.16626920582, 0.13957067793, 0.10715922047, 0.07036604749, 0.030753242  },
{  0.02715245941, 0.06225352394, 0.09515851168, 0.1246289713, 0.1495959888, 0.1691565194, 0.182603415, 0.1894506105, 0.1894506105, 0.182603415, 0.1691565194, 0.1495959888, 0.1246289713, 0.09515851168, 0.06225352394, 0.02715245941  },
{  0.02414830287, 0.0554595294, 0.0850361483, 0.1118838472, 0.1351363685, 0.1540457611, 0.1680041022, 0.1765627054, 0.1794464704, 0.1765627054, 0.1680041022, 0.1540457611, 0.1351363685, 0.1118838472, 0.0850361483, 0.0554595294, 0.02414830287  },
{  0.0216160135, 0.0497145489, 0.0764257303, 0.1009420441, 0.1225552067, 0.1406429147, 0.1546846751, 0.1642764837, 0.169142383, 0.169142383, 0.1642764837, 0.1546846751, 0.1406429147, 0.1225552067, 0.1009420441, 0.0764257303, 0.0497145489, 0.0216160135  },
{  0.0194617882, 0.0448142268, 0.0690445427, 0.091490022, 0.111566646, 0.128753963, 0.142606702, 0.152766042, 0.158968843, 0.16105445, 0.158968843, 0.152766042, 0.142606702, 0.128753963, 0.111566646, 0.091490022, 0.0690445427, 0.0448142268, 0.0194617882 },
{  0.0176140071, 0.04060143, 0.062672048, 0.083276742, 0.10193012, 0.118194532, 0.131688638, 0.142096109, 0.149172986, 0.152753387, 0.152753387, 0.149172986, 0.142096109, 0.131688638, 0.118194532, 0.10193012, 0.083276742, 0.062672048, 0.04060143, 0.0176140071  } };

int main()
{
    int i, j;
    raizes = fopen("raizesDaqui.dat", "w");
    pesos = fopen("pesosDaqui.dat", "w");

    for (i = 0;i < 20;i++) {
        for (j = 0;j < 20;j++) {
            if (x_k[i][j] >= 0) {
                fprintf(raizes, " ");
            }
            if (w_k[i][j] >= 0) {
                fprintf(pesos, " ");
            }
            fprintf(raizes, "%.16f ", x_k[i][j]); /* (%.nf imprime float com n casas decimais) */
            fprintf(pesos, "%.16f ", w_k[i][j]);
        }
        fprintf(raizes, "\n\n");
        fprintf(pesos, "\n\n");
    }

    fclose(raizes);
    fclose(pesos);
    return 0;
}