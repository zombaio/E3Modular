
#pragma once

#include "JuceHeader.h"

namespace e3
{
    class TabComponent : public TabbedComponent
    {
    public:
        TabComponent(TabbedButtonBar::Orientation o, int gap=0) :
            TabbedComponent(o),
            gap_(gap)
        {}

        void resized() override;

    private:
        int gap_;
    };

} // namespace e3