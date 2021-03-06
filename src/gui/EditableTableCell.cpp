
#include "gui/TableComponent.h"
#include "gui/EditableTableCell.h"


namespace e3 {

    EditableTableCell::EditableTableCell(TableComponent* owner) :
        Label("EditableTableCell", ""),
        owner_(owner)
    {
        setEditable(false, false, true);
    }


    void EditableTableCell::paint(Graphics& g)
    {
        if (isBeingEdited() == false) {
            owner_->paintCell(g, row_, column_, getWidth(), getHeight(), owner_->isRowSelected(row_));
        }
        else {
            Label::paint(g);
        }
    }


    void EditableTableCell::setRowAndColumn( int row, int column )
    {
        row_ = row;
        column_ = column;
        std::string text = owner_->getText( row_, column_ );
        setText( text, dontSendNotification );
    }


    void EditableTableCell::mouseDown(const MouseEvent& e)
    {
        if (e.mods.isLeftButtonDown() &&        // open on editor on ctrl-click
            (e.mods.isCtrlDown()) &&
            (e.getNumberOfClicks() == 1))
        {
            showEditor();
        }
        else {
            Component* parent = getParentComponent();
            if (parent != nullptr) {
                MouseEvent e1 = e.getEventRelativeTo(parent);
                parent->mouseDown(e1);
            }
        }
    }


    void EditableTableCell::mouseDoubleClick(const MouseEvent& e)
    {
        Component* parent = getParentComponent();
        if (parent != nullptr) {
            MouseEvent e1 = e.getEventRelativeTo(parent);
            parent->mouseDoubleClick(e1);
        }
    }


    void EditableTableCell::textWasEdited()
    {
        owner_->setText(getText().toStdString(), row_, column_);
    }

} // namespace e3