/** @file MaxRectsBinPack.h
 @author Jukka Jylänki

 @brief Implements different bin packer algorithms that use the MAXRECTS data structure.

 This work is released to Public Domain, do whatever you want with it.
 */

#ifndef __MAXRECTSBINPACK_H__
#define __MAXRECTSBINPACK_H__

#include <vector>
#include "rbp_Rect.h"

namespace rbp
{
    /** MaxRectsBinPack implements the MAXRECTS data structure and different bin packing algorithms that
     use this structure. */
    class MaxRectsBinPack
    {
    public:
        /// Instantiates a bin of size (0,0). Call Init to create a new bin.
        MaxRectsBinPack();

        /// Instantiates a bin of the given size.
        MaxRectsBinPack(int width, int height);

        /// (Re)initializes the packer to an empty bin of width x height units. Call whenever
        /// you need to restart with a new bin.
        void init(int width, int height);

        Rect insert(int width, int height);

    private:
        Rect findPositionForNewNodeBottomLeft(int width, int height, int& bestY, int& bestX) const;

        /// @return True if the free node was split.
        bool splitFreeNode(Rect freeNode, const Rect& usedNode);

        /// Goes through the free rectangle list and removes any redundant entries.
        void pruneFreeList();

    private:
        int _binWidth;
        int _binHeight;
        std::vector<Rect> _freeRectangles;
    };
}

#endif
