#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <sstream>

#include "xxx.h"
#include "classdef.h"
#include "language.h"
#include "translator_en.h"

using namespace std;

// Auxiliary macro to write the <message> element with testing for "unfinished".
#define WRITE_MESSAGE_ELEMENT(comment, en, tr)                              \
{                                                                           \
    fout << "    <message>\n"                                               \
        "        <comment>" << comment << "</comment>\n"                    \
        "        <source>" << en << "</source>\n";                          \
    if (en == tr)                                                           \
        fout << "        <translation type=\"unfinished\"></translation>\n";\
    else                                                                    \
        fout << "        <translation>" << tr << "</translation>\n";        \
    fout << "    </message>\n";                                             \
}


#define WRITE_ELEMENT(method)               \
{                                           \
    Config_setBool(false);                  \
    string en{ trEn.method() };             \
    string tr{ theTranslator->method() };   \
    WRITE_MESSAGE_ELEMENT(#method, en, tr); \
}


#define WRITE_ELEMENT_WITH_C_OPTIMIZATION(method)   \
{                                                   \
    Config_setBool(false);                          \
    string en{ trEn.method() };                     \
    string tr{ theTranslator->method() };           \
    WRITE_MESSAGE_ELEMENT(#method, en, tr);         \
    Config_setBool(true); /* emulate OPTIMIZE_OUTPUT_FOR_C is True */ \
    en = trEn.method();                             \
    tr = theTranslator->method();                   \
    WRITE_MESSAGE_ELEMENT(#method " OPTIMIZE_OUTPUT_FOR_C", en, tr); \
}

#define WRITE_ELEMENT_WITH_JAVA_OPTIMIZATION(method)\
{                                                   \
    Config_setBool(false);                          \
    string en{ trEn.method() };                     \
    string tr{ theTranslator->method() };           \
    WRITE_MESSAGE_ELEMENT(#method, en, tr);         \
    Config_setBool(true); /* emulate OPTIMIZE_OUTPUT_JAVA is True */ \
    en = trEn.method();                             \
    tr = theTranslator->method();                   \
    WRITE_MESSAGE_ELEMENT(#method " OPTIMIZE_OUTPUT_JAVA", en, tr); \
}

#define WRITE_ELEMENT_EXTRACTALL(method)                        \
{                                                               \
    Config_setBool(false);                                      \
    string en{ trEn.method(false) };                            \
    string tr{ theTranslator->method(false) };                  \
    WRITE_MESSAGE_ELEMENT(#method " DontExtractAll", en, tr);   \
    en = trEn.method(true);                                     \
    tr = theTranslator->method(true);                           \
    WRITE_MESSAGE_ELEMENT(#method " ExtractAll", en, tr);       \
}

#define WRITE_ELEMENT_SINGULAR(method)                  \
{                                                       \
    Config_setBool(false);                              \
    string en{ trEn.method(false) };                    \
    string tr{ theTranslator->method(false) };          \
    WRITE_MESSAGE_ELEMENT(#method " Plural", en, tr);   \
    en = trEn.method(true);                             \
    tr = theTranslator->method(true);                   \
    WRITE_MESSAGE_ELEMENT(#method " Singular", en, tr); \
}


#define WRITE_ELEMENT_ENABLE(method)\
{ \
    Config_setBool(false); \
    string en{ trEn.method(false) };             \
    string tr{ theTranslator->method(false) };   \
    WRITE_MESSAGE_ELEMENT(#method " Disabled", en, tr); \
    en = trEn.method(true);                     \
    tr = theTranslator->method(true);           \
    WRITE_MESSAGE_ELEMENT(#method " Enabled", en, tr); \
}


#define WRITE_ELEMENT_EXTRACTALL_WITH_C_OPTIMIZATION(method)\
{ \
    Config_setBool(false); \
    string en{ trEn.method(false) };             \
    string tr{ theTranslator->method(false) };   \
    WRITE_MESSAGE_ELEMENT(#method " DontExtractAll", en, tr); \
    en = trEn.method(true);                     \
    tr = theTranslator->method(true);           \
    WRITE_MESSAGE_ELEMENT(#method " ExtractAll", en, tr); \
    Config_setBool(true); /* emulate OPTIMIZE_OUTPUT_FOR_C is True */ \
    en = trEn.method(false);                     \
    tr = theTranslator->method(false);           \
    WRITE_MESSAGE_ELEMENT(#method " DontExtractAll", en, tr); \
    en = trEn.method(true);                     \
    tr = theTranslator->method(true);           \
    WRITE_MESSAGE_ELEMENT(#method " ExtractAll", en, tr); \
}


#define WRITE_ELEMENT1(method)\
{ \
    Config_setBool(false); \
    string en{ trEn.method("%1") };             \
    string tr{ theTranslator->method("%1") };   \
    WRITE_MESSAGE_ELEMENT(#method, en, tr);     \
}

#define WRITE_ELEMENT1REF(method)\
{ \
    Config_setBool(false); \
    QCString a{"%1"}; \
    string en{ trEn.method(a) };             \
    string tr{ theTranslator->method(a) };   \
    WRITE_MESSAGE_ELEMENT(#method, en, tr);  \
}

// The following macro produces result for the Doxygen method that took
// a number as the argument, and generated the template string with @0, @1, etc.
// placeholders for the list items. The code of the method should be changed
// to the code that returns a single %1 placeholder for the entire list.
// The string representation of the list should be constructed separately
// using the trLSep, trLSepAnd2, and trLSepAnd language-dependent separator.
// This macro generates the new templates for a singular or plural (based
// on the number of elements).
#define WRITE_ELEMENT1INT(method)\
{ \
    Config_setBool(false);                                          \
    string en{ trEn.method(1) };    /* single element */            \
    string::size_type pos;                                          \
    pos = en.find("@0");                                            \
    if (pos != string::npos) { en.replace(pos, 2, "%1"); }          \
                                                                    \
    string tr{ theTranslator->method(1) };                          \
    pos = tr.find("@0");                                            \
    if (pos != string::npos) { tr.replace(pos, 2, "%1"); }          \
    WRITE_MESSAGE_ELEMENT(#method " Singular", en, tr);             \
                                                                    \
    en = trEn.method(5);    /* phrase for 5 elements */             \
    pos = en.find("@0");                                            \
    string::size_type pos2;                                         \
    pos2 = en.find("@4");                                           \
    if (pos2 != string::npos)                                       \
    {                                                               \
        en.replace(en.begin() + pos, en.begin() + pos2 + 2, "%1");  \
    }                                                               \
    tr = theTranslator->method(5);                                  \
    pos = tr.find("@0");                                            \
    pos2 = tr.find("@4");                                           \
    if (pos2 != string::npos)                                       \
    {                                                               \
        tr.replace(tr.begin() + pos, tr.begin() + pos2 + 2, "%1");  \
    }                                                               \
    WRITE_MESSAGE_ELEMENT(#method " Plural", en, tr);               \
}

#define WRITE_ELEMENT2(method)\
{ \
    Config_setBool(false); \
    string en{ trEn.method("%1", "%2") };             \
    string tr{ theTranslator->method("%1", "%2") };   \
    WRITE_MESSAGE_ELEMENT(#method, en, tr);     \
}

#define WRITE_ELEMENT_COMPOUNDTYPE_SINGULAR(method)\
{ \
    Config_setBool(false); \
    std::string result{ "Undefined" }; \
    for (auto compType: list<ClassDef::CompoundType>{ ClassDef::Class, ClassDef::Struct, ClassDef::Union, ClassDef::Interface, \
	                      ClassDef::Protocol, ClassDef::Category, ClassDef::Exception }) { \
		switch (compType)                                       \
		{														\
		case ClassDef::Class:      result = "Class"; break;		\
		case ClassDef::Struct:     result = "Struct"; break;	\
		case ClassDef::Union:      result = "Union"; break;		\
		case ClassDef::Interface:  result = "Interface"; break;	\
		case ClassDef::Protocol:   result = "Protocol"; break;	\
		case ClassDef::Category:   result = "Category"; break;	\
		case ClassDef::Exception:  result = "Exception"; break;	\
		default: break;											\
		}														\
        string en{ trEn.method(compType, false) };              \
        string tr{ theTranslator->method(compType, false) };    \
        WRITE_MESSAGE_ELEMENT(#method " Plural", en, tr);       \
        en = trEn.method(compType, true);                       \
        tr = theTranslator->method(compType, true);             \
        WRITE_MESSAGE_ELEMENT(#method " Singular", en, tr);     \
	} \
}


#define WRITE_ELEMENT_NAME_COMPOUNDTYPE_TEMPLATE(method)\
{ \
    Config_setBool(false); \
    std::string result{ "Undefined" }; \
    for (auto compType: list<ClassDef::CompoundType>{ ClassDef::Class, ClassDef::Struct, ClassDef::Union, ClassDef::Interface, \
	                      ClassDef::Protocol, ClassDef::Category, ClassDef::Exception }) { \
		switch (compType)                                           \
		{														    \
		case ClassDef::Class:      result = "Class"; break;		    \
		case ClassDef::Struct:     result = "Struct"; break;	    \
		case ClassDef::Union:      result = "Union"; break;		    \
		case ClassDef::Interface:  result = "Interface"; break;	    \
		case ClassDef::Protocol:   result = "Protocol"; break;	    \
		case ClassDef::Category:   result = "Category"; break;	    \
		case ClassDef::Exception:  result = "Exception"; break;	    \
		default: break;											    \
		}														    \
        string en{ trEn.method("%1", compType, false) };            \
        string tr{ theTranslator->method("%1", compType, false) };  \
        WRITE_MESSAGE_ELEMENT(#method " NotTemplate", en, tr);      \
        en = trEn.method("%1", compType, true);                     \
        tr = theTranslator->method("%1", compType, true);           \
        WRITE_MESSAGE_ELEMENT(#method " IsTemplate", en, tr);       \
	} \
}


#define WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(method)\
{ \
    Config_setBool(false); \
    string en{ trEn.method(true, true) };            \
    string tr{ theTranslator->method(true, true) };  \
    WRITE_MESSAGE_ELEMENT(#method " FirstCapital Singular", en, tr);    \
    en = trEn.method(true, false);            \
    tr = theTranslator->method(true, false);  \
    WRITE_MESSAGE_ELEMENT(#method " FirstCapital Plural", en, tr);    \
    en = trEn.method(false, true);            \
    tr = theTranslator->method(false, true);  \
    WRITE_MESSAGE_ELEMENT(#method " FirstSmall Singular", en, tr);    \
    en = trEn.method(false, false);            \
    tr = theTranslator->method(false, false);  \
    WRITE_MESSAGE_ELEMENT(#method " FirstSmall Plural", en, tr);    \
}



void GenerateTranslatorSentences(const std::string& lang_readable,
                                 const std::string& fname_suffix,
                                 const std::string& xx_XX = "")
{
    cerr << "Generating translations for " << lang_readable << " ... ";

    // Construct the File Name, and open the file for writing.
    string fname{ "doxy_" + fname_suffix + ".ts2" };
    ofstream  fout(fname);

    // If the file could not be open, finish with error message.
    if (!fout.is_open())
    {
        cerr << "Open for output to '" << fname << "' failed.\n";
        exit(1);
    }

    // File was open for writing. Generate the output.
    //
    // Create the translator object for the language (and also the English one).
    setTranslator(lang_readable);
    if (theTranslator == nullptr)
    {
        cerr << "ERROR\n    The translator for '" << lang_readable << "' could not be instantiated (skipped).\n";
        return;
    }

    TranslatorEnglish trEn;

    //------------------------------------------------------------------------------------
    // The document heading.
    fout << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
            "<!DOCTYPE TS>\n"
            "<TS version=\"2.0\"";
    if (!xx_XX.empty())
    {
        fout << " language=\"" << xx_XX << "\"";
    }
    fout << ">\n";

    //------------------------------------------------------------------------------------
    // The RTF context
    fout << "<context>\n"
            "    <name>doxy-rtf</name>\n";


    WRITE_ELEMENT(trRTFansicp);
    WRITE_ELEMENT(trRTFCharSet);

    fout << "</context>\n";

    //------------------------------------------------------------------------------------
    // The Text context.
    fout << "<context>\n"
            "    <name>doxy-text</name>\n";

    // Some tricks from the older code (throw it away after clarification).
#if 0

    fout << "\n<! --trWriteList() should be replaced using\n"
        "     &trLSep;, &trLSepAnd2;, and &trLSepAnd; sentences\n\n";

    WriteSentence(fout, "trWriteList1", theTranslator->trWriteList(1));
    WriteSentence(fout, "trWriteList2", theTranslator->trWriteList(2));
    WriteSentence(fout, "trWriteList3", theTranslator->trWriteList(3));

    fout << "-->\n\n";

    // Extract the separator definitions.
    //
    std::string sAnd(theTranslator->trWriteList(3));
    std::string s;

    std::string::size_type pos = sAnd.find("@1");
    s = sAnd.substr(2, pos-2);

    sAnd.erase(0, pos+2);
    pos = sAnd.find("@2");
    sAnd.erase(pos);

    std::string sAnd2(theTranslator->trWriteList(2));

    pos = sAnd2.find("@1");
    sAnd2.erase(pos);
    sAnd2.erase(0, 2);

    WriteSentence(fout, "trLSep", s);
    WriteSentence(fout, "trLSepAnd", sAnd);
    WriteSentence(fout, "trLSepAnd2", sAnd2);

    fout << "\n<!-- Should be normal Sentence templates instead using "
        "trWriteList inside -->\n\n";

    // The original.
    //
    fout << "<!--\n";
    WriteSentence(fout, "trInheritsList",
        theTranslator->trInheritsList(1));
    WriteSentence(fout, "trInheritsList",
        theTranslator->trInheritsList(2));
    WriteSentence(fout, "trInheritsList",
        theTranslator->trInheritsList(3));
    fout << "-->\n";

    // Two entitities possible -- inheriting from one and many.
    //
    s = theTranslator->trInheritsList(1);
    pos = s.find("@0");
    s.replace(pos, 2, "%1");

    WriteSentence(fout, "trInherits", s);

    s = theTranslator->trInheritsList(2);
    pos = s.find("@0");
    std::string::size_type pos2 = s.find("@1");
    s.replace(pos, pos2-pos+2, "%1");

    WriteSentence(fout, "trInheritsList", s);
    //-----------------------------------------------------------------

    fout << "<!--\n";
    WriteSentence(fout, "trInheritedByList",
        theTranslator->trInheritedByList(1));
    WriteSentence(fout, "trInheritedByList",
        theTranslator->trInheritedByList(2));
    WriteSentence(fout, "trInheritedByList",
        theTranslator->trInheritedByList(3));
    fout << "-->\n";

    s = theTranslator->trInheritedByList(1);
    pos = s.find("@0");
    s.replace(pos, 2, "%1");

    WriteSentence(fout, "trInheritedBy", s);

    s = theTranslator->trInheritedByList(2);
    pos = s.find("@0");
    pos2 = s.find("@1");
    s.replace(pos, pos2-pos+2, "%1");

    WriteSentence(fout, "trInheritedByList", s);
    //-----------------------------------------------------------------

    fout << "<!--\n";
    WriteSentence(fout, "trReimplementedFromList",
        theTranslator->trReimplementedFromList(1));
    WriteSentence(fout, "trReimplementedFromList",
        theTranslator->trReimplementedFromList(2));
    WriteSentence(fout, "trReimplementedFromList",
        theTranslator->trReimplementedFromList(3));
    fout << "-->\n";

    s = theTranslator->trReimplementedFromList(1);
    pos = s.find("@0");
    s.replace(pos, 2, "%1");

    WriteSentence(fout, "trReimplementedFrom", s);

    s = theTranslator->trReimplementedFromList(2);
    pos = s.find("@0");
    pos2 = s.find("@1");
    s.replace(pos, pos2-pos+2, "%1");

    WriteSentence(fout, "trReimplementedFromList", s);
    //-----------------------------------------------------------------

    fout << "<!--\n";
    WriteSentence(fout, "trReimplementedInList",
        theTranslator->trReimplementedInList(1));
    WriteSentence(fout, "trReimplementedInList",
        theTranslator->trReimplementedInList(2));
    WriteSentence(fout, "trReimplementedInList",
        theTranslator->trReimplementedInList(3));
    fout << "-->\n";

    s = theTranslator->trReimplementedInList(1);
    pos = s.find("@0");
    s.replace(pos, 2, "%1");

    WriteSentence(fout, "trReimplementedIn", s);

    s = theTranslator->trReimplementedInList(2);
    pos = s.find("@0");
    pos2 = s.find("@1");
    s.replace(pos, pos2-pos+2, "%1");

    WriteSentence(fout, "trReimplementedInList", s);
    //-----------------------------------------------------------------
#endif

    // The language readable identification from the translator first.
    WRITE_ELEMENT(idLanguage);

    // Extract the separator definitions -- see the Translators Revisited
    // for reasoning.
    //
    // Use the list with 3 elements. The English translator returns
    // the result like "@0, @1, and @2". The ", " will be the separator
    // between the items not separated "and". The ", and" is the separator
    // of the last two items when the list has more than two elements.
    {
        // Fistly for the English translator
        std::string enAnd{ trEn.trWriteList(3) };
        std::string::size_type pos = enAnd.find("@1");
        std::string enSep{ enAnd.substr(2, pos - 2) };   // after @0, before @1
        enAnd.erase(0, pos + 2);         // cut the prefix including the @1
        pos = enAnd.find("@2");
        enAnd.erase(pos);                // cut the tail from @2 included

        // Now use the list with 2 elements. The English translator should return
        // the result like "@0 and @1" -- that is " and " without the comma.
        // That separator should be used for lists with exactly two elements.
        std::string enAnd2(trEn.trWriteList(2));
        pos = enAnd2.find("@1");
        enAnd2.erase(pos);       // erase the tail with @1 included
        enAnd2.erase(0, 2);      // erase the @0

        // The same for theTranslator
        std::string trAnd{ theTranslator->trWriteList(3) };
        pos = trAnd.find("@1");
        std::string trSep{ trAnd.substr(2, pos - 2) };   // after @0, before @1
        trAnd.erase(0, pos + 2);         // cut the prefix including the @1
        pos = trAnd.find("@2");
        trAnd.erase(pos);                // cut the tail from @2 included

        // Now use the list with 2 elements.
        std::string trAnd2(theTranslator->trWriteList(2));
        pos = trAnd2.find("@1");
        trAnd2.erase(pos);       // erase the tail with @1 included
        trAnd2.erase(0, 2);      // erase the @0

        WRITE_MESSAGE_ELEMENT("trLSep", enSep, trSep);
        WRITE_MESSAGE_ELEMENT("trLSepAnd", enAnd, trAnd);
        WRITE_MESSAGE_ELEMENT("trLSepAnd2", enAnd2, trAnd2);
        //
        // NOTE: The English implementation in 1.8.12 actually returns ", and"
        // for bothe And, and And2 (they should differ). Some languages
        // use the same value for bote And and And2. Some languages do not use
        // any equivalent of "and". And some languages put a space even
        // in front of the comma.

    }

    // The following source was taken directly from the translator.h,
	// (at the time of Doxygen version 1.8.12) and the
    // virtual method identifies were wrapped to the macros. In cases when
    // the OPTIMIZE_OUTPUT_FOR_C setting makes a difference, the method was
    // called twice with different macros. In cases when the method produces
    // a different message based on a boolean argument, the macro variations
	// for True and False was called. Some macros combine the "optimize for C"
	// with the boolean argument.
	//
	// When the method argument is to be inserted into the message as a value
	// (e.g. name of a method), the placeholder like "%1" is passed to the macro.

    //////////////////////////////////////////
    // --- Language control methods -------------------

    // The following was moved up... WRITE_ELEMENT(idLanguage);
    WRITE_ELEMENT(latexLanguageSupportCommand);

    // --- Language translation methods -------------------

    WRITE_ELEMENT(trRelatedFunctions);
    WRITE_ELEMENT(trRelatedSubscript);
    WRITE_ELEMENT(trDetailedDescription);
    WRITE_ELEMENT(trMemberTypedefDocumentation);
    WRITE_ELEMENT(trMemberEnumerationDocumentation);

	// Only the Japanese translato uses OPTIMIZE_OUTPUT_JAVA and only on a single place.
	if (lang_readable == "japanese")
	{
		WRITE_ELEMENT_WITH_JAVA_OPTIMIZATION(trMemberFunctionDocumentation);
	}
	else
	{
		WRITE_ELEMENT(trMemberFunctionDocumentation);
	}

	WRITE_ELEMENT_WITH_C_OPTIMIZATION(trMemberDataDocumentation);
    WRITE_ELEMENT(trMore);
    WRITE_ELEMENT(trListOfAllMembers);
    WRITE_ELEMENT(trMemberList);
    WRITE_ELEMENT(trThisIsTheListOfAllMembers);
    WRITE_ELEMENT(trIncludingInheritedMembers);
    WRITE_ELEMENT1(trGeneratedAutomatically);
    WRITE_ELEMENT(trEnumName);
    WRITE_ELEMENT(trEnumValue);
    WRITE_ELEMENT(trDefinedIn);


    // quick reference sections

    WRITE_ELEMENT(trModules);
    WRITE_ELEMENT(trClassHierarchy);
    WRITE_ELEMENT_WITH_C_OPTIMIZATION(trCompoundList);
    WRITE_ELEMENT(trFileList);
    WRITE_ELEMENT(trCompoundMembers);
    WRITE_ELEMENT_WITH_C_OPTIMIZATION(trFileMembers);
    WRITE_ELEMENT(trRelatedPages);
    WRITE_ELEMENT(trExamples);
    WRITE_ELEMENT(trSearch);
    WRITE_ELEMENT(trClassHierarchyDescription);
    WRITE_ELEMENT_EXTRACTALL(trFileListDescription);
    WRITE_ELEMENT_WITH_C_OPTIMIZATION(trCompoundListDescription);
    WRITE_ELEMENT_EXTRACTALL(trCompoundMembersDescription);
    WRITE_ELEMENT_EXTRACTALL_WITH_C_OPTIMIZATION(trFileMembersDescription);

    WRITE_ELEMENT(trExamplesDescription);
    WRITE_ELEMENT(trRelatedPagesDescription);
    WRITE_ELEMENT(trModulesDescription);


    // index titles (the project name is prepended for these)

    WRITE_ELEMENT(trDocumentation);
    WRITE_ELEMENT(trModuleIndex);
    WRITE_ELEMENT(trHierarchicalIndex);
    WRITE_ELEMENT_WITH_C_OPTIMIZATION(trCompoundIndex);
	WRITE_ELEMENT(trFileIndex);
    WRITE_ELEMENT(trModuleDocumentation);
    WRITE_ELEMENT_WITH_C_OPTIMIZATION(trClassDocumentation);
	WRITE_ELEMENT(trFileDocumentation);
    WRITE_ELEMENT(trExampleDocumentation);
    WRITE_ELEMENT(trPageDocumentation);
    WRITE_ELEMENT(trReferenceManual);
    WRITE_ELEMENT(trDefines);
    WRITE_ELEMENT(trTypedefs);
    WRITE_ELEMENT(trEnumerations);
    WRITE_ELEMENT(trFunctions);
    WRITE_ELEMENT(trVariables);
    WRITE_ELEMENT(trEnumerationValues);
    WRITE_ELEMENT(trDefineDocumentation);
    WRITE_ELEMENT(trTypedefDocumentation);
    WRITE_ELEMENT(trEnumerationTypeDocumentation);
    WRITE_ELEMENT(trFunctionDocumentation);
    WRITE_ELEMENT(trVariableDocumentation);
    WRITE_ELEMENT_WITH_C_OPTIMIZATION(trCompounds);
	WRITE_ELEMENT2(trGeneratedAt);
	WRITE_ELEMENT1(trClassDiagram);
	WRITE_ELEMENT(trForInternalUseOnly);
    WRITE_ELEMENT(trWarning);
    WRITE_ELEMENT(trVersion);
    WRITE_ELEMENT(trDate);
    WRITE_ELEMENT(trReturns);
    WRITE_ELEMENT(trSeeAlso);
    WRITE_ELEMENT(trParameters);
    WRITE_ELEMENT(trExceptions);
    WRITE_ELEMENT(trGeneratedBy);

    //////////////////////////////////////////////////////////////////////////
    // new since 0.49-990307
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trNamespaceList);
	WRITE_ELEMENT_EXTRACTALL(trNamespaceListDescription);
	WRITE_ELEMENT(trFriends);

    //////////////////////////////////////////////////////////////////////////
    // new since 0.49-990405
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trRelatedFunctionDocumentation);

    //////////////////////////////////////////////////////////////////////////
    // new since 0.49-990425
    //////////////////////////////////////////////////////////////////////////

	WRITE_ELEMENT_NAME_COMPOUNDTYPE_TEMPLATE(trCompoundReference);
	WRITE_ELEMENT1(trFileReference);
    WRITE_ELEMENT1(trNamespaceReference);

    WRITE_ELEMENT(trPublicMembers);
    WRITE_ELEMENT(trPublicSlots);
    WRITE_ELEMENT(trSignals);
    WRITE_ELEMENT(trStaticPublicMembers);
    WRITE_ELEMENT(trProtectedMembers);
    WRITE_ELEMENT(trProtectedSlots);
    WRITE_ELEMENT(trStaticProtectedMembers);
    WRITE_ELEMENT(trPrivateMembers);
    WRITE_ELEMENT(trPrivateSlots);
    WRITE_ELEMENT(trStaticPrivateMembers);
    WRITE_ELEMENT1INT(trWriteList);
    WRITE_ELEMENT1INT(trInheritsList);
    WRITE_ELEMENT1INT(trInheritedByList);
    WRITE_ELEMENT1INT(trReimplementedFromList);
    WRITE_ELEMENT1INT(trReimplementedInList);
    WRITE_ELEMENT(trNamespaceMembers);
	WRITE_ELEMENT_EXTRACTALL(trNamespaceMemberDescription);
	WRITE_ELEMENT(trNamespaceIndex);
    WRITE_ELEMENT(trNamespaceDocumentation);

    //////////////////////////////////////////////////////////////////////////
    // new since 0.49-990522
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trNamespaces);

    //////////////////////////////////////////////////////////////////////////
    // new since 0.49-990728
    //////////////////////////////////////////////////////////////////////////

	WRITE_ELEMENT_COMPOUNDTYPE_SINGULAR(trGeneratedFromFiles);

    //////////////////////////////////////////////////////////////////////////
    // new since 0.49-990901
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trReturnValues);
    WRITE_ELEMENT(trMainPage);
    WRITE_ELEMENT(trPageAbbreviation);

    //////////////////////////////////////////////////////////////////////////
    // new since 0.49-991003
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trDefinedAtLineInSourceFile);
    WRITE_ELEMENT(trDefinedInSourceFile);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.0.0
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT1(trCollaborationDiagram);
    WRITE_ELEMENT1(trInclDepGraph);
    WRITE_ELEMENT(trConstructorDocumentation);
    WRITE_ELEMENT(trGotoSourceCode);
    WRITE_ELEMENT(trGotoDocumentation);
    WRITE_ELEMENT(trPrecondition);
    WRITE_ELEMENT(trPostcondition);
    WRITE_ELEMENT(trInvariant);
    WRITE_ELEMENT(trInitialValue);
    WRITE_ELEMENT(trCode);

    WRITE_ELEMENT(trGraphicalHierarchy);
    WRITE_ELEMENT(trGotoGraphicalHierarchy);
    WRITE_ELEMENT(trGotoTextualHierarchy);
    WRITE_ELEMENT(trPageIndex);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.1.0
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trNote);
    WRITE_ELEMENT(trPublicTypes);
    WRITE_ELEMENT_WITH_C_OPTIMIZATION(trPublicAttribs);
	WRITE_ELEMENT(trStaticPublicAttribs);
    WRITE_ELEMENT(trProtectedTypes);
    WRITE_ELEMENT(trProtectedAttribs);
    WRITE_ELEMENT(trStaticProtectedAttribs);
    WRITE_ELEMENT(trPrivateTypes);
    WRITE_ELEMENT(trPrivateAttribs);
    WRITE_ELEMENT(trStaticPrivateAttribs);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.1.4
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trReferencedBy);
    WRITE_ELEMENT(trRemarks);
    WRITE_ELEMENT(trAttention);
    WRITE_ELEMENT(trInclByDepGraph);
    WRITE_ELEMENT(trSince);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.1.5
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trLegendTitle);
    WRITE_ELEMENT(trLegendDocs);
    WRITE_ELEMENT(trLegend);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.2
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trProperties);
    WRITE_ELEMENT(trPropertyDocumentation);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.4
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT_WITH_C_OPTIMIZATION(trClasses);
    WRITE_ELEMENT1(trPackage);
    WRITE_ELEMENT(trPackageList);
    WRITE_ELEMENT(trPackageListDescription);
    WRITE_ELEMENT(trPackages);
    WRITE_ELEMENT(trDefineValue);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.6
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trRTFGeneralIndex);

    // Translation of the word

    WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(trClass);
	WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(trFile);
	WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(trNamespace);
	WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(trGroup);
	WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(trPage);
	WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(trMember);
	WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(trGlobal);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.7
    //////////////////////////////////////////////////////////////////////////

	WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(trAuthor);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.11
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trReferences);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.13
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT1INT(trImplementedFromList);
    WRITE_ELEMENT1INT(trImplementedInList);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.16
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trRTFTableOfContents);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.2.18
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trEvents);
    WRITE_ELEMENT(trEventDocumentation);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.3
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trPackageTypes);
    WRITE_ELEMENT(trPackageMembers);
    WRITE_ELEMENT(trStaticPackageMembers);
    WRITE_ELEMENT(trPackageAttribs);
    WRITE_ELEMENT(trStaticPackageAttribs);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.3.1
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trAll);
    WRITE_ELEMENT(trCallGraph);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.3.3
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trSearchResultsTitle);
    WRITE_ELEMENT1INT(trSearchResults);
    WRITE_ELEMENT(trSearchMatches);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.3.8
    //////////////////////////////////////////////////////////////////////////

	WRITE_ELEMENT1REF(trSourceFile);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.3.9
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trDirIndex);
    WRITE_ELEMENT(trDirDocumentation);
    WRITE_ELEMENT(trDirectories);
    WRITE_ELEMENT(trDirDescription);
    WRITE_ELEMENT1(trDirReference);
    WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(trDir);

	//////////////////////////////////////////////////////////////////////////
    // new since 1.4.1
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trOverloadText);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.4.6
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trCallerGraph);
    WRITE_ELEMENT(trEnumerationValueDocumentation);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.5.4
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trMemberFunctionDocumentationFortran);
    WRITE_ELEMENT(trCompoundListFortran);
    WRITE_ELEMENT(trCompoundMembersFortran);
    WRITE_ELEMENT(trCompoundListDescriptionFortran);
    WRITE_ELEMENT_EXTRACTALL_WITH_C_OPTIMIZATION(trCompoundMembersDescriptionFortran);
    WRITE_ELEMENT(trCompoundIndexFortran);
    WRITE_ELEMENT(trTypeDocumentation);
    WRITE_ELEMENT(trSubprograms);
    WRITE_ELEMENT(trSubprogramDocumentation);
    WRITE_ELEMENT(trDataTypes);
    WRITE_ELEMENT(trModulesList);
    WRITE_ELEMENT_EXTRACTALL(trModulesListDescription);
    WRITE_ELEMENT_NAME_COMPOUNDTYPE_TEMPLATE(trCompoundReferenceFortran);
    WRITE_ELEMENT1(trModuleReference);
    WRITE_ELEMENT(trModulesMembers);
    WRITE_ELEMENT_EXTRACTALL(trModulesMemberDescription);
    WRITE_ELEMENT(trModulesIndex);
    WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(trModule);
    WRITE_ELEMENT_COMPOUNDTYPE_SINGULAR(trGeneratedFromFilesFortran);
    WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(trType);
    WRITE_ELEMENT_FIRSTCAPITAL_SINGULAR(trSubprogram);
    WRITE_ELEMENT(trTypeConstraints);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.6.0
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT1(trDirRelation);
    WRITE_ELEMENT(trLoading);
    WRITE_ELEMENT(trGlobalNamespace);
    WRITE_ELEMENT(trSearching);
    WRITE_ELEMENT(trNoMatches);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.6.3
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT1(trFileIn);
    WRITE_ELEMENT1(trIncludesFileIn);
    ///??? virtual QCString trDateTime(int year, int month, int day, int dayOfWeek,
    ///???     int hour, int minutes, int seconds, trFileMembersDescription
    ///???     bool includeTime) = 0;

    //////////////////////////////////////////////////////////////////////////
    // new since 1.7.5
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trCiteReferences);
    WRITE_ELEMENT(trCopyright);
    WRITE_ELEMENT1(trDirDepGraph);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.8.0
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trDetailLevel);
    WRITE_ELEMENT(trTemplateParameters);
    WRITE_ELEMENT1(trAndMore);  ///\todo Should be int argument as the value makes difference (singular, plural)
    WRITE_ELEMENT_SINGULAR(trEnumGeneratedFromFiles);
    WRITE_ELEMENT1(trEnumReference);
    WRITE_ELEMENT2(trInheritedFrom);
    WRITE_ELEMENT(trAdditionalInheritedMembers);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.8.2
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT_ENABLE(trPanelSynchronisationTooltip);
    WRITE_ELEMENT(trProvidedByCategory);
    WRITE_ELEMENT(trExtendsClass);
    WRITE_ELEMENT(trClassMethods);
    WRITE_ELEMENT(trInstanceMethods);
    WRITE_ELEMENT(trMethodDocumentation);
    WRITE_ELEMENT(trDesignOverview);

    //////////////////////////////////////////////////////////////////////////
    // new since 1.8.4
    //////////////////////////////////////////////////////////////////////////

    WRITE_ELEMENT(trInterfaces);
    WRITE_ELEMENT(trServices);
    WRITE_ELEMENT(trConstantGroups);
    WRITE_ELEMENT1(trConstantGroupReference);
    WRITE_ELEMENT1(trServiceReference);
    WRITE_ELEMENT1(trSingletonReference);
    WRITE_ELEMENT_SINGULAR(trServiceGeneratedFromFiles);
    WRITE_ELEMENT_SINGULAR(trSingletonGeneratedFromFiles);

    //----------------------------------------------------------------------
    fout << "</context>\n";
    fout.close();

    std::cerr << "\n";
}


int main()
{
    GenerateTranslatorSentences("afrikaans", "af", "af_ZA");
    GenerateTranslatorSentences("arabic", "ar", "ar_SA");
    GenerateTranslatorSentences("armenian", "am", "am_ET");
    GenerateTranslatorSentences("brazilian", "pt_br", "pt_BR");
    GenerateTranslatorSentences("catalan", "ca", "ca_ES");
    GenerateTranslatorSentences("chinese", "zh", "zh_CN");
    GenerateTranslatorSentences("chinese-traditional", "zh_tw", "zh_TW");
    GenerateTranslatorSentences("croatian", "hr", "hr_HR");
    GenerateTranslatorSentences("czech", "cz", "cs_CZ");
    GenerateTranslatorSentences("danish", "da", "da_DK");
    GenerateTranslatorSentences("dutch", "nl", "nl_NL");
    GenerateTranslatorSentences("english", "en", "en_EN");
    GenerateTranslatorSentences("esperanto", "es", "es_ES");
    GenerateTranslatorSentences("finnish", "fi", "fi_FI");
    GenerateTranslatorSentences("french", "fr", "fr_FR");
    GenerateTranslatorSentences("german", "de", "de_DE");
    GenerateTranslatorSentences("greek", "el", "el_GR");
    GenerateTranslatorSentences("hungarian", "hu", "hu_HU");
    GenerateTranslatorSentences("indonesian", "id", "id_ID");
    GenerateTranslatorSentences("italian", "it", "it_IT");
    GenerateTranslatorSentences("japanese", "ja", "ja_JP");
    GenerateTranslatorSentences("japanese-en", "ja_en", "ja_JP");
    GenerateTranslatorSentences("korean", "ko", "ko_KR");
    GenerateTranslatorSentences("korean-en", "ko_en", "ko_KR");
    GenerateTranslatorSentences("latvian", "lv", "lv_LV");
    GenerateTranslatorSentences("lithuanian", "lt", "lt_LT");
    GenerateTranslatorSentences("macedonian", "mk", "mk_MK");
    GenerateTranslatorSentences("norwegian", "nb", "nb_NO");
    GenerateTranslatorSentences("persian", "fa", "fa_IR");
    GenerateTranslatorSentences("polish", "pl", "pl_PL");
    GenerateTranslatorSentences("portuguese", "pt", "pt_PT");
    GenerateTranslatorSentences("romanian", "ro", "ro_MD");
    GenerateTranslatorSentences("russian", "ru", "ru_RU");
    GenerateTranslatorSentences("serbian", "sr", "sr_CS");
    GenerateTranslatorSentences("serbian-cyrillic", "sr_cyrillic", "sr_CS");
    GenerateTranslatorSentences("slovak", "sk", "sk_SK");
    GenerateTranslatorSentences("slovene", "sl", "sl_SI");
    GenerateTranslatorSentences("spanish", "es", "es_ES");
    GenerateTranslatorSentences("swedish", "sv", "sv_SE");
    GenerateTranslatorSentences("turkish", "tr", "tr_TR");
    GenerateTranslatorSentences("ukrainian", "uk", "uk_UA");
    GenerateTranslatorSentences("vietnamese", "vi", "vi_VN");

	return 0;
}
