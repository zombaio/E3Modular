
#pragma once

#include <string>


namespace juce {
    class XmlElement;
}

namespace e3 {

    class Bank;
    class Instrument;
    class Module;
    class Parameter;

    using juce::XmlElement;


    class BankSerializer
    {
    public:
        static XmlElement* readBank(const std::string& path);
        static XmlElement* createNewBank();
        static void storeBank(const std::string& path, XmlElement* root);

        static Instrument* loadInstrument(XmlElement* root, int hash);

        static void storeInstrument(XmlElement* root, Instrument* instrument);

        //static void toString(const Bank& bank, std::string& result);

    protected:
        static void readInstrument(XmlElement* element, Instrument* instrument);
        static void readModules(XmlElement* parent, Instrument* instrument);
        static void readParameters(XmlElement* parent, Module* module);
        static void readParameter(XmlElement* parent, Parameter& p);
        static void readLinks(XmlElement* parent, Module* module);

        static void writeBank(XmlElement* const e, const Bank* const bank);
        static void writeInstrument(XmlElement* const e, const Instrument* instrument, int& hash);
        static void writeModule(XmlElement* const e, const Module* module);
        static void writeParameters(XmlElement* const e, const Module* module);
        static void writeParameter(XmlElement* const e, const Parameter& param, const Parameter& defaultParam);
        static void writeLinks(XmlElement* const e, const Module* module);

        static File checkPath(const std::string& path);
        static void checkRoot(XmlElement* root);
        static int createHash(XmlElement* e);

        static std::string defaultBankXml;
    };


} // namespace e3