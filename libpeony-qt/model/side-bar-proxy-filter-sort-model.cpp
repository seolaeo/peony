#include "side-bar-proxy-filter-sort-model.h"
#include "side-bar-abstract-item.h"

using namespace Peony;

SideBarProxyFilterSortModel::SideBarProxyFilterSortModel(QObject *parent) : QSortFilterProxyModel(parent)
{

}

bool SideBarProxyFilterSortModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    auto index = sourceModel()->index(sourceRow, 0, sourceParent);
    auto item = static_cast<SideBarAbstractItem*>(index.internalPointer());
    if (item) {
        if (item->displayName().at(0) == ".") {
            return false;
        }
    }
    return true;
}

bool SideBarProxyFilterSortModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    auto leftItem = static_cast<SideBarAbstractItem*>(left.internalPointer());
    auto rightItem = static_cast<SideBarAbstractItem*>(right.internalPointer());
    if (leftItem->type() != SideBarAbstractItem::FileSystemItem || rightItem->type() != SideBarAbstractItem::FileSystemItem) {
        return true;
    }
    return leftItem->displayName() < rightItem->displayName();
}

SideBarAbstractItem *SideBarProxyFilterSortModel::itemFromIndex(const QModelIndex &proxy_index)
{
    auto index = mapToSource(proxy_index);
    return static_cast<SideBarAbstractItem*>(index.internalPointer());
}
