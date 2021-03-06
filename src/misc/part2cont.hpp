// ------------------------------------------------------------------------ 
//  Copyright (C)
//  ETH Zurich - Switzerland
// 
//  Kevis-Kokitsi Maninis <kmaninis@vision.ee.ethz.ch>
//  Jordi Pont-Tuset <jponttuset@vision.ee.ethz.ch>
//  July 2016
// ------------------------------------------------------------------------ 
// This file is part of the COB package presented in:
//    K.K. Maninis, J. Pont-Tuset, P. Arbelaez and L. Van Gool 
//    Convolutional Oriented Boundaries
//    European Conference on Computer Vision (ECCV), 2016 
// Please consider citing the paper if you use this code.
// ------------------------------------------------------------------------
#ifndef PART2CONT_HPP
#define PART2CONT_HPP

#include <iostream>
#include "containers.hpp"
#include <Eigen/Dense>


contour_container part2cont(const Eigen::Array<label_type,Eigen::Dynamic,Eigen::Dynamic>& lp)
{
    /* Sizes */
    std::size_t sx = lp.rows();
    std::size_t sy = lp.cols();


    /*-------------------------------------------------------------*/
    /*           Create LUT of from pairs of regions to            */
    /*             list of contours and UCM threshold              */
    /*-------------------------------------------------------------*/
    contour_container pairs_contours;
    
    /* Scan horizontal contours*/
    for (std::size_t xx=1; xx<sx; ++xx)
    {
        for (std::size_t yy=0; yy<sy; ++yy)
        {
            if (lp(xx,yy)!=lp(xx-1,yy))
            {
                /* Build a contour element and the two labels 'touching' it*/
                label_type lab1 = std::min(lp(xx,yy),lp(xx-1,yy));
                label_type lab2 = std::max(lp(xx,yy),lp(xx-1,yy));

                /* Recover the element or build and empty one */
                /* and push the contour piece                 */
                pairs_contours[std::make_pair(lab1,lab2)].push_back(cont_elem(2*xx,2*yy+1));
            }
        }
    }

    /* Scan vertical contours*/
    for (std::size_t xx=0; xx<sx; ++xx)
    {
        for (std::size_t yy=1; yy<sy; ++yy)
        {
            if (lp(xx,yy)!=lp(xx,yy-1))
            {
                /* Build a contour element and the two labels 'touching' it*/
                label_type lab1 = std::min(lp(xx,yy),lp(xx,yy-1));
                label_type lab2 = std::max(lp(xx,yy),lp(xx,yy-1));

                /* Recover the element or build and empty one */
                /* and push the contour piece                 */
                pairs_contours[std::make_pair(lab1,lab2)].push_back(cont_elem(2*xx+1,2*yy));
            }
        }
    }
    
    return pairs_contours;
}



#endif
