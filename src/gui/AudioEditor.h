/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/
#pragma once

#include <memory>
#include "JuceHeader.h"
#include "gui/CommandTarget.h"
#include "gui/Skin.h"


namespace e3 {

    class Processor;
    class ToolPanel;
    class StackedPanel;
    class EditorPanel;
    class BrowserPanel;


    class AudioEditor : public AudioProcessorEditor, public CommandTarget
    {
    public:
        AudioEditor(Processor*);
        ~AudioEditor();

        void paint(Graphics&) override;
        void resized() override;

        void createIcon(Image& image);

        bool perform(const InvocationInfo& info) override;      // Implementation for ApplicationCommandTarget
        static ApplicationCommandManager& getCommandManager();

        enum PanelIds {
            kEditorPanel = 0,
            kBrowserPanel = 1,
            kAudioPanel = 2
        };

        ScopedPointer<Skin> skin_;
        ScopedPointer<ToolPanel> toolPanel_;
        ScopedPointer<StackedPanel> stackedPanel_;
        ScopedPointer<EditorPanel>  editorPanel_;
        ScopedPointer<BrowserPanel> browserPanel_;
#ifdef BUILD_TARGET_APP
        ScopedPointer<AudioDeviceSelectorComponent>  audioPanel_;
#endif
    private:
        bool restoreWindowStateFromString(const std::string& s);
        void createComponents();

        Processor* processor_;

        ScopedPointer<ResizableCornerComponent> resizer_;
        ComponentBoundsConstrainer resizeLimits_;

        static ScopedPointer<ApplicationCommandManager> commandManager_;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioEditor)
    };

} // namespace e3