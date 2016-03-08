/** @file MaxRectsBinPack.cpp
 @author Jukka Jylänki

 @brief Implements different bin packer algorithms that use the MAXRECTS data structure.

 This work is released to Public Domain, do whatever you want with it.
 */
#include <utility>
#include <iostream>
#include <limits>

#include <cassert>
#include <cstring>
#include <cmath>
#include "rbp_MaxRectsBinPack.h"
using namespace std;

namespace rbp
{
    MaxRectsBinPack::MaxRectsBinPack() : _binWidth(0), _binHeight(0)
    {
    }

    MaxRectsBinPack::MaxRectsBinPack(int width, int height)
    {
        init(width, height);
    }

    void MaxRectsBinPack::init(int width, int height)
    {
        _binWidth = width;
        _binHeight = height;

        Rect n;
        n.x = 0;
        n.y = 0;
        n.width = width;
        n.height = height;

        _freeRectangles.clear();
        _freeRectangles.push_back(n);
    }

    Rect MaxRectsBinPack::insert(int width, int height)
    {
        Rect newNode;
        int score1;  // Unused in this function. We don't need to know the score after finding the position.
        int score2;

        newNode = findPositionForNewNodeBottomLeft(width, height, score1, score2);

        if (newNode.height == 0)
        {
            return newNode;
        }

        size_t numRectanglesToProcess = _freeRectangles.size();
        for (size_t i = 0; i < numRectanglesToProcess; ++i)
        {
            if (splitFreeNode(_freeRectangles[i], newNode))
            {
                _freeRectangles.erase(_freeRectangles.begin() + i);
                --i;
                --numRectanglesToProcess;
            }
        }

        pruneFreeList();
        return newNode;
    }

    Rect MaxRectsBinPack::findPositionForNewNodeBottomLeft(int width, int height, int& bestY, int& bestX) const
    {
        Rect bestNode;
        memset(&bestNode, 0, sizeof(Rect));

        bestY = std::numeric_limits<int>::max();

        for (size_t i = 0; i < _freeRectangles.size(); ++i)
        {
            // Try to place the rectangle in upright (non-flipped) orientation.
            if (_freeRectangles[i].width >= width && _freeRectangles[i].height >= height)
            {
                int topSideY = _freeRectangles[i].y + height;
                if (topSideY < bestY || (topSideY == bestY && _freeRectangles[i].x < bestX))
                {
                    bestNode.x = _freeRectangles[i].x;
                    bestNode.y = _freeRectangles[i].y;
                    bestNode.width = width;
                    bestNode.height = height;
                    bestY = topSideY;
                    bestX = _freeRectangles[i].x;
                }
            }

            if (_freeRectangles[i].width >= height && _freeRectangles[i].height >= width)
            {
                int topSideY = _freeRectangles[i].y + width;
                if (topSideY < bestY || (topSideY == bestY && _freeRectangles[i].x < bestX))
                {
                    bestNode.x = _freeRectangles[i].x;
                    bestNode.y = _freeRectangles[i].y;
                    bestNode.width = height;
                    bestNode.height = width;
                    bestY = topSideY;
                    bestX = _freeRectangles[i].x;
                }
            }
        }
        return bestNode;
    }

    bool MaxRectsBinPack::splitFreeNode(Rect freeNode, const Rect& usedNode)
    {
        // Test with SAT if the rectangles even intersect.
        if (usedNode.x >= freeNode.x + freeNode.width || usedNode.x + usedNode.width <= freeNode.x ||
            usedNode.y >= freeNode.y + freeNode.height || usedNode.y + usedNode.height <= freeNode.y)
        {
            return false;
        }

        if (usedNode.x < freeNode.x + freeNode.width && usedNode.x + usedNode.width > freeNode.x)
        {
            // New node at the top side of the used node.
            if (usedNode.y > freeNode.y && usedNode.y < freeNode.y + freeNode.height)
            {
                Rect newNode = freeNode;
                newNode.height = usedNode.y - newNode.y;
                _freeRectangles.push_back(newNode);
            }

            // New node at the bottom side of the used node.
            if (usedNode.y + usedNode.height < freeNode.y + freeNode.height)
            {
                Rect newNode = freeNode;
                newNode.y = usedNode.y + usedNode.height;
                newNode.height = freeNode.y + freeNode.height - (usedNode.y + usedNode.height);
                _freeRectangles.push_back(newNode);
            }
        }

        if (usedNode.y < freeNode.y + freeNode.height && usedNode.y + usedNode.height > freeNode.y)
        {
            // New node at the left side of the used node.
            if (usedNode.x > freeNode.x && usedNode.x < freeNode.x + freeNode.width)
            {
                Rect newNode = freeNode;
                newNode.width = usedNode.x - newNode.x;
                _freeRectangles.push_back(newNode);
            }

            // New node at the right side of the used node.
            if (usedNode.x + usedNode.width < freeNode.x + freeNode.width)
            {
                Rect newNode = freeNode;
                newNode.x = usedNode.x + usedNode.width;
                newNode.width = freeNode.x + freeNode.width - (usedNode.x + usedNode.width);
                _freeRectangles.push_back(newNode);
            }
        }

        return true;
    }

    void MaxRectsBinPack::pruneFreeList()
    {
        /// Go through each pair and remove any rectangle that is redundant.
        for (size_t i = 0; i < _freeRectangles.size(); ++i)
        {
            for (size_t j = i + 1; j < _freeRectangles.size(); ++j)
            {
                if (IsContainedIn(_freeRectangles[i], _freeRectangles[j]))
                {
                    _freeRectangles.erase(_freeRectangles.begin() + i);
                    --i;
                    break;
                }
                if (IsContainedIn(_freeRectangles[j], _freeRectangles[i]))
                {
                    _freeRectangles.erase(_freeRectangles.begin() + j);
                    --j;
                }
            }
        }
    }
}
