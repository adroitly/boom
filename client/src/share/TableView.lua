
local M = class("share.TableView", function(size, delegate)
	return cc.TableView:create(size)
end)

-- 废弃，请使用GridView
function M:ctor(size, delegate)
	self:setDirection(cc.SCROLLVIEW_DIRECTION_VERTICAL)
	self:setDelegate()
    self:setVerticalFillOrder(cc.TABLEVIEW_FILL_TOPDOWN)

	assert(delegate.onTableViewCellTouched and delegate.onTableViewCellSize and 
		delegate.onTableViewCellAtIndex and delegate.onTableViewCellCount)
    
	self:registerScriptHandler(function(table, cell)
        delegate:onTableViewCellTouched(table, cell)
    end,cc.TABLECELL_TOUCHED)

    self:registerScriptHandler(function(table, idx)
        return delegate:onTableViewCellSize(table, idx)
    end,cc.TABLECELL_SIZE_FOR_INDEX)

    self:registerScriptHandler(function(table, idx)
        return delegate:onTableViewCellAtIndex(table, idx)
    end,cc.TABLECELL_SIZE_AT_INDEX)

    self:registerScriptHandler(function(table)
        return delegate:onTableViewCellCount(table)
    end,cc.NUMBER_OF_CELLS_IN_TABLEVIEW)

    if delegate.onScrollViewDidScroll then
        self:registerScriptHandler(function(table)
            delegate:onScrollViewDidScroll(table)
        end, cc.SCROLLVIEW_SCRIPT_SCROLL)
    end

    if delegate.onScrollViewDidZoom then
        self:registerScriptHandler(function(table)
            delegate:onScrollViewDidZoom(table)
        end, cc.SCROLLVIEW_SCRIPT_ZOOM)
    end
    self:reloadData()
end

return M