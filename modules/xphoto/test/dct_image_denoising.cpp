#include "test_precomp.hpp"

namespace cvtest
{
    TEST(xphoto_dctimagedenoising, regression)
    {
        cv::String dir = cvtest::TS::ptr()->get_data_path() + "dct_image_denoising/";
        int nTests = 1;

        double thresholds[] = {0.1};

        int psize[] = {8};
        double sigma[] = {9.0};

        for (int i = 0; i < nTests; ++i)
        {
            cv::String srcName = dir + cv::format( "sources/%02d.png", i + 1);
            cv::Mat src = cv::imread( srcName, 1 );

            cv::String previousResultName = dir + cv::format( "results/%02d.png", i + 1 );
            cv::Mat previousResult = cv::imread( previousResultName, 1 );

            cv::Mat currentResult, fastNlMeansResult;

            cv::dctDenoising(src, currentResult, sigma[i], psize[i]);

            cv::Mat sqrError = ( currentResult - previousResult )
                .mul( currentResult - previousResult );
            cv::Scalar mse = cv::sum(sqrError) / cv::Scalar::all( double(sqrError.total()*sqrError.channels()) );

            EXPECT_LE( mse[0] + mse[1] + mse[2] + mse[3], thresholds[i] );
        }
    }
}