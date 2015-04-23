
#pragma once

#include <string>
#include "JuceHeader.h"
#include "core/ModuleBase.h"
#include "gui/Wire.h"



namespace e3 {

    class EditorPanel;
    class PortComponent;
    class Wire;


    class ModuleComponent : public Component
    {
    public:
        ModuleComponent(EditorPanel* owner, Module* module);
        ~ModuleComponent();

        void mouseDoubleClick(const MouseEvent& e) override;

        void focusAndSelect(bool focus, bool select);
        void moveTo(Rectangle<int>& r);
        PortComponent* getPort(uint16_t portId, PortType portType);
        void getDockingPosition(uint16_t portId, PortType portType, Point<int>& pos);
        void collapseOrExpand(bool collapse);
        bool isCollapsed();

        void createComponents();
        void createWires();
        void removeWires(uint16_t targetId);
        void removeWire(const Link& link, PortType portType);
        void positionWires(ModuleComponent* movedComponent);
        void drawWires(Graphics& g);
        void addWire(const Link& link, Wire* wire);
        void hitTestWires(const Rectangle<int>& rc, WireMap& map);
        Wire* getWire(const Link& link);

        void setColors();
        void drawBackgroundRect(Graphics& g, Rectangle<int>& updateRect);

        Module* getModule() const   { return module_;  }
        uint16_t getModuleId() const { return module_->id_;  }

    protected:
        void calculateSize();
        void setPortVisibility();
        void deleteWire(const Link& link);
        //int getTextBlockHeight(const std::string& s, Font& font);


        EditorPanel* owner_;
        Module* module_;

        const int portHeight_ = 12;
        bool selected_        = false;
        bool focused_         = false;

        Colour colBkgnd_, colFrame_, colPort_, colText_;

        WireMap wires_;
        ScopedPointer<Label> label_;

        typedef OwnedArray<PortComponent> PortList;
        PortList inports_;
        PortList outports_;
    };

} // namespace e3