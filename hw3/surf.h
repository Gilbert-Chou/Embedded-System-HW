#ifndef SURF_H
#define SURF_H
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QImage>
#include <QPixmap>
#include <iostream>

class Surf{
public:
    Surf(cv::Mat obj): _obj(obj){}

    QImage doImage(cv::Mat tar){
        cv::Mat dst = tar.clone();
        int minHessian = 425;
        double max_dist, min_dist;
        cv::SurfFeatureDetector detector( minHessian );
        std::vector<cv::KeyPoint> keypoints_1, keypoints_2;
        cv::SurfDescriptorExtractor extractor;
        cv::Mat descriptors_1, descriptors_2;
        cv::FlannBasedMatcher matcher;
        std::vector< cv::DMatch > matches;
        std::vector< cv::DMatch > good_matches;
        std::vector<cv::Point2f> obj_corners(4);


        detector.detect( _obj, keypoints_1 );
        extractor.compute( _obj, keypoints_1, descriptors_1 );
        obj_corners[0] = cvPoint(0,0); obj_corners[1] = cvPoint( _obj.cols, 0 );
        obj_corners[2] = cvPoint( _obj.cols, _obj.rows ); obj_corners[3] = cvPoint( 0, _obj.rows );

        cv::Mat mask_img = dst.clone();

        while(true){
            max_dist = 0; min_dist = 100;
            detector.detect( mask_img, keypoints_2 );
            extractor.compute( mask_img, keypoints_2, descriptors_2 );
            matcher.match( descriptors_1, descriptors_2, matches );

            for(int i = 0; i < descriptors_1.rows; i++){
                double dist = matches[i].distance;
                if(dist < min_dist) min_dist = dist;
                if(dist > max_dist) max_dist = dist;
            }
            good_matches.clear();
            for(int i = 0; i < descriptors_1.rows; i++){
                if(matches[i].distance <= cv::max(2*min_dist, 0.02))
                    good_matches.push_back( matches[i]);
            }
            std::cout << good_matches.size() << std::endl;
            if(good_matches.size() <= 7) break;

            std::vector<cv::Point2f> obj, scene;
            for(int i = 0; i < good_matches.size(); i++){
                obj.push_back( keypoints_1[ good_matches[i].queryIdx ].pt );
                scene.push_back( keypoints_2[ good_matches[i].trainIdx ].pt );
            }

            cv::Mat H = cv::findHomography( obj, scene, CV_RANSAC );
            std::vector<cv::Point2f> scene_corners(4);
            cv::perspectiveTransform( obj_corners, scene_corners, H);

            cv::line( dst, scene_corners[0], scene_corners[1], cv::Scalar( 0, 255, 0), 4 );
            cv::line( dst, scene_corners[1], scene_corners[2], cv::Scalar( 0, 255, 0), 4 );
            cv::line( dst, scene_corners[2], scene_corners[3], cv::Scalar( 0, 255, 0), 4 );
            cv::line( dst, scene_corners[3], scene_corners[0], cv::Scalar( 0, 255, 0), 4 );

            cv::rectangle(mask_img, scene_corners[0], scene_corners[2], cv::Scalar(0, 0, 0), CV_FILLED);

        }
        cv::resize(dst, dst, cv::Size(400, 300));
        return convertProcess(dst);

    }

    QImage convertProcess(cv::Mat img){
        if(img.type() == CV_8UC1){
            return QImage((unsigned char*)img.data, img.cols, img.rows, img.step, QImage::Format_Indexed8).copy();
        }
        else{
            cv::Mat dst;
            img.copyTo(dst);
            cv::cvtColor(dst, dst, CV_BGR2RGB);
            return QImage((unsigned char*)dst.data, dst.cols, dst.rows, dst.step, QImage::Format_RGB888).copy();
        }
    }

private:
    cv::Mat _obj;
};

#endif // SURF_H

