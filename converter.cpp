#include <fstream>
#include <iostream>
#include <string>

#include "language.h"

using namespace std;

void GenerateAllTranslatorSentences();
void WriteHeading(ofstream & fout,
                  const string & CountryName,
                  const string & CharsetId);
void WriteSentence(ofstream & fout,
                   const string & SentenceId,
                   const string & SentenceBody);
void GenerateTranslatorSentences(const string & sLang);


void GenerateAllTranslatorSentences()
{
    GenerateTranslatorSentences("Afrikaans");
    GenerateTranslatorSentences("Arabic");
    GenerateTranslatorSentences("Armenian");
    GenerateTranslatorSentences("Brazilian Portuguese");
    GenerateTranslatorSentences("Catalan");
    GenerateTranslatorSentences("Chinese");
    GenerateTranslatorSentences("Chinese Traditional");
    GenerateTranslatorSentences("Croatian");
    GenerateTranslatorSentences("Czech");
    GenerateTranslatorSentences("Danish");
    GenerateTranslatorSentences("Dutch");
    GenerateTranslatorSentences("English");
    GenerateTranslatorSentences("Esperanto");
    GenerateTranslatorSentences("Finnish");
    GenerateTranslatorSentences("French");
    GenerateTranslatorSentences("German");
    GenerateTranslatorSentences("Greek");
    GenerateTranslatorSentences("Hungarian");
    GenerateTranslatorSentences("Indonesian");
    GenerateTranslatorSentences("Italian");
    GenerateTranslatorSentences("Japanese");
    GenerateTranslatorSentences("Japanese-en");
    GenerateTranslatorSentences("Korean");
    GenerateTranslatorSentences("Korean-en");
    GenerateTranslatorSentences("Latvian");
    GenerateTranslatorSentences("Lithuanian");
    GenerateTranslatorSentences("Macedonian");
    GenerateTranslatorSentences("Norwegian");
    GenerateTranslatorSentences("Persian");
    GenerateTranslatorSentences("Polish");
    GenerateTranslatorSentences("Portuguese");
    GenerateTranslatorSentences("Romanian");
    GenerateTranslatorSentences("Russian");
    GenerateTranslatorSentences("Serbian");
    GenerateTranslatorSentences("SerbianCyrillic");
    GenerateTranslatorSentences("Slovak");
    GenerateTranslatorSentences("Slovene");
    GenerateTranslatorSentences("Spanish");
    GenerateTranslatorSentences("Swedish");
    GenerateTranslatorSentences("Turkish");
    GenerateTranslatorSentences("Ukrainian");
    GenerateTranslatorSentences("Vietnamese");
}


void WriteHeading(ofstream & fout,
                  const string & CountryName,
                  const string & CharsetId)
{
    //???
    printf("<translator id=\"%s\"", CountryName);
    printf(" charset=\"%s\">\n", CharsetId);
}


void WriteSentence(ofstream & fout,
                   const string & SentenceId,
                   const string & SentenceBody)
{   
    // Sentence beginning
    fout << "<sentence id=\"" << SentenceId << "\">";
    
    // Now output the body.
    fout << SentenceBody;
    
    // Close the definition.
    fout << "</sentence>\n";      
}


void GenerateTranslatorSentences(const string & sLang)
{
    fprintf(stderr, 
            "Generating sentence definitions for %s ... ", 
            sLang.data());
            
    // Construct the File Name.
    string Filename("Translator_" + sLang + ".xml");

#if 0    
    //???
    // Open the file for writing.
    //
    QTextStream fout;
    fout.open(Filename);

    // If the file could not be open, finish with error message.
    //
    if (! fout.is_open())
    {
        fprintf(stderr, 
                "Open for output to %s failed.\n", 
                Filename);
        exit(1);
    }
#endif
    
    // File was open for writing. Generate the output.
    //
    // If the translator object exists, delete it. New one will
    // be created immediately.
    //
    if (theTranslator != nullptr)
        delete theTranslator;

    // Set the language.
    setTranslator(sLang);
    
    // Generate Sentence definitions for all translator methods.
    // Created for version 1.2.12
    //
    WriteHeading(fout, theTranslator->idLanguage(), 
                       theTranslator->idLanguageCharset());
    
    fout << "<!-- Simple sentences -->\n\n";

    WriteSentence(fout, "trReferences",
        theTranslator->trReferences());

    WriteSentence(fout, "trAlphabeticalList",
        theTranslator->trAlphabeticalList());
    
    WriteSentence(fout, "idLanguage",
        theTranslator->idLanguage());
    
    WriteSentence(fout, "latexLanguageSupportCommand",
        theTranslator->latexLanguageSupportCommand());
    
    WriteSentence(fout, "idLanguageCharset",
        theTranslator->idLanguageCharset());
    
    WriteSentence(fout, "trRelatedFunctions",
        theTranslator->trRelatedFunctions());
    
    WriteSentence(fout, "trRelatedSubscript",
        theTranslator->trRelatedSubscript());
    
    WriteSentence(fout, "trDetailedDescription",
        theTranslator->trDetailedDescription());
    
    WriteSentence(fout, "trMemberTypedefDocumentation",
        theTranslator->trMemberTypedefDocumentation());
    
    WriteSentence(fout, "trMemberEnumerationDocumentation",
        theTranslator->trMemberEnumerationDocumentation());
    
    WriteSentence(fout, "trMemberFunctionDocumentation",
        theTranslator->trMemberFunctionDocumentation());
    
    Config_setBool(TRUE);
    WriteSentence(fout, "trMemberDataDocumentationC",
        theTranslator->trMemberDataDocumentation());

    Config_setBool(FALSE);
    WriteSentence(fout, "trMemberDataDocumentation",
        theTranslator->trMemberDataDocumentation());

    WriteSentence(fout, "trMore",
        theTranslator->trMore());
    
    WriteSentence(fout, "trListOfAllMembers",
        theTranslator->trListOfAllMembers());
    
    WriteSentence(fout, "trMemberList",
        theTranslator->trMemberList());
    
    WriteSentence(fout, "trEnumName",
        theTranslator->trEnumName());
    
    WriteSentence(fout, "trEnumValue",
        theTranslator->trEnumValue());
    
    WriteSentence(fout, "trDefinedIn",
        theTranslator->trDefinedIn());
    
    WriteSentence(fout, "trModules",
        theTranslator->trModules());
    
    WriteSentence(fout, "trClassHierarchy",
        theTranslator->trClassHierarchy());
    
    Config_setBool(TRUE);
    WriteSentence(fout, "trCompoundListC",
        theTranslator->trCompoundList());
    
    Config_setBool(FALSE);
    WriteSentence(fout, "trCompoundList",
        theTranslator->trCompoundList());
    
    WriteSentence(fout, "trFileList",
        theTranslator->trFileList());
    
    Config_setBool(TRUE);
    WriteSentence(fout, "trHeaderFilesC",
        theTranslator->trHeaderFiles());
    
    Config_setBool(FALSE);
    WriteSentence(fout, "trHeaderFiles",
        theTranslator->trHeaderFiles());
    
    WriteSentence(fout, "trCompoundMembers",
        theTranslator->trCompoundMembers());
    
    Config_setBool(TRUE);
    WriteSentence(fout, "trFileMembersC",
        theTranslator->trFileMembers());
    
    Config_setBool(FALSE);
    WriteSentence(fout, "trFileMembers",
        theTranslator->trFileMembers());
    
    WriteSentence(fout, "trRelatedPages",
        theTranslator->trRelatedPages());
    
    WriteSentence(fout, "trExamples",
        theTranslator->trExamples());
    
    WriteSentence(fout, "trSearch",
        theTranslator->trSearch());
    
    WriteSentence(fout, "trClassHierarchyDescription",
        theTranslator->trClassHierarchyDescription());
    
    Config_setBool(TRUE);
    WriteSentence(fout, "trCompoundListDescriptionC",
        theTranslator->trCompoundListDescription());
    
    Config_setBool(FALSE);
    WriteSentence(fout, "trCompoundListDescription",
        theTranslator->trCompoundListDescription());
    
    WriteSentence(fout, "trHeaderFilesDescription",
        theTranslator->trHeaderFilesDescription());
    
    WriteSentence(fout, "trExamplesDescription",
        theTranslator->trExamplesDescription());
    
    WriteSentence(fout, "trRelatedPagesDescription",
        theTranslator->trRelatedPagesDescription());
    
    WriteSentence(fout, "trModulesDescription",
        theTranslator->trModulesDescription());
    
    WriteSentence(fout, "trNoDescriptionAvailable",
        theTranslator->trNoDescriptionAvailable());
    
    WriteSentence(fout, "trDocumentation",
        theTranslator->trDocumentation());
    
    WriteSentence(fout, "trModuleIndex",
        theTranslator->trModuleIndex());
    
    WriteSentence(fout, "trHierarchicalIndex",
        theTranslator->trHierarchicalIndex());
    
    Config_setBool(TRUE);
    WriteSentence(fout, "trCompoundIndexC",
        theTranslator->trCompoundIndex());
    
    Config_setBool(FALSE);
    WriteSentence(fout, "trCompoundIndex",
        theTranslator->trCompoundIndex());
    
    WriteSentence(fout, "trFileIndex",
        theTranslator->trFileIndex());
    
    WriteSentence(fout, "trModuleDocumentation",
        theTranslator->trModuleDocumentation());
    
    Config_setBool(TRUE);
    WriteSentence(fout, "trClassDocumentationC",
        theTranslator->trClassDocumentation());
    
    Config_setBool(FALSE);
    WriteSentence(fout, "trClassDocumentation",
        theTranslator->trClassDocumentation());
    
    WriteSentence(fout, "trFileDocumentation",
        theTranslator->trFileDocumentation());
    
    WriteSentence(fout, "trExampleDocumentation",
        theTranslator->trExampleDocumentation());
    
    WriteSentence(fout, "trPageDocumentation",
        theTranslator->trPageDocumentation());
    
    WriteSentence(fout, "trReferenceManual",
        theTranslator->trReferenceManual());
    
    WriteSentence(fout, "trDefines",
        theTranslator->trDefines());
    
    WriteSentence(fout, "trFuncProtos",
        theTranslator->trFuncProtos());
    
    WriteSentence(fout, "trTypedefs",
        theTranslator->trTypedefs());
    
    WriteSentence(fout, "trEnumerations",
        theTranslator->trEnumerations());
    
    WriteSentence(fout, "trFunctions",
        theTranslator->trFunctions());
    
    WriteSentence(fout, "trVariables",
        theTranslator->trVariables());
    
    WriteSentence(fout, "trEnumerationValues",
        theTranslator->trEnumerationValues());
    
    WriteSentence(fout, "trDefineDocumentation",
        theTranslator->trDefineDocumentation());
    
    WriteSentence(fout, "trFunctionPrototypeDocumentation",
        theTranslator->trFunctionPrototypeDocumentation());
    
    WriteSentence(fout, "trTypedefDocumentation",
        theTranslator->trTypedefDocumentation());
    
    WriteSentence(fout, "trEnumerationTypeDocumentation",
        theTranslator->trEnumerationTypeDocumentation());
    
    WriteSentence(fout, "trEnumerationValueDocumentation",
        theTranslator->trEnumerationValueDocumentation());
    
    WriteSentence(fout, "trFunctionDocumentation",
        theTranslator->trFunctionDocumentation());
    
    WriteSentence(fout, "trVariableDocumentation",
        theTranslator->trVariableDocumentation());
    
    Config_setBool(TRUE);
    WriteSentence(fout, "trCompoundsC",
        theTranslator->trCompounds());
    
    Config_setBool(FALSE);
    WriteSentence(fout, "trCompounds",
        theTranslator->trCompounds());
    
    WriteSentence(fout, "trWrittenBy",
        theTranslator->trWrittenBy());
    
    WriteSentence(fout, "trForInternalUseOnly",
        theTranslator->trForInternalUseOnly());
    
    WriteSentence(fout, "trReimplementedForInternalReasons",
        theTranslator->trReimplementedForInternalReasons());
    
    WriteSentence(fout, "trWarning",
        theTranslator->trWarning());
    
    WriteSentence(fout, "trBugsAndLimitations",
        theTranslator->trBugsAndLimitations());
    
    WriteSentence(fout, "trVersion",
        theTranslator->trVersion());
    
    WriteSentence(fout, "trDate",
        theTranslator->trDate());
    
    WriteSentence(fout, "trReturns",
        theTranslator->trReturns());
    
    WriteSentence(fout, "trSeeAlso",
        theTranslator->trSeeAlso());
    
    WriteSentence(fout, "trParameters",
        theTranslator->trParameters());
    
    WriteSentence(fout, "trExceptions",
        theTranslator->trExceptions());
    
    WriteSentence(fout, "trGeneratedBy",
        theTranslator->trGeneratedBy());
    
    WriteSentence(fout, "trNamespaceList",
        theTranslator->trNamespaceList());
    
    WriteSentence(fout, "trFriends",
        theTranslator->trFriends());
    
    WriteSentence(fout, "trRelatedFunctionDocumentation",
        theTranslator->trRelatedFunctionDocumentation());
    
    WriteSentence(fout, "trPublicMembers",
        theTranslator->trPublicMembers());
    
    WriteSentence(fout, "trPublicSlots",
        theTranslator->trPublicSlots());
    
    WriteSentence(fout, "trSignals",
        theTranslator->trSignals());
    
    WriteSentence(fout, "trStaticPublicMembers",
        theTranslator->trStaticPublicMembers());
    
    WriteSentence(fout, "trProtectedMembers",
        theTranslator->trProtectedMembers());
    
    WriteSentence(fout, "trProtectedSlots",
        theTranslator->trProtectedSlots());
    
    WriteSentence(fout, "trStaticProtectedMembers",
        theTranslator->trStaticProtectedMembers());
    
    WriteSentence(fout, "trPrivateMembers",
        theTranslator->trPrivateMembers());
    
    WriteSentence(fout, "trPrivateSlots",
        theTranslator->trPrivateSlots());
    
    WriteSentence(fout, "trStaticPrivateMembers",
        theTranslator->trStaticPrivateMembers());
    
    WriteSentence(fout, "trNamespaceMembers",
        theTranslator->trNamespaceMembers());
    
    WriteSentence(fout, "trNamespaceIndex",
        theTranslator->trNamespaceIndex());
    
    WriteSentence(fout, "trNamespaceDocumentation",
        theTranslator->trNamespaceDocumentation());
    
    WriteSentence(fout, "trNamespaces",
        theTranslator->trNamespaces());
    
    WriteSentence(fout, "trAlphabeticalList",
        theTranslator->trAlphabeticalList());
    
    WriteSentence(fout, "trReturnValues",
        theTranslator->trReturnValues());
    
    WriteSentence(fout, "trMainPage",
        theTranslator->trMainPage());
    
    WriteSentence(fout, "trPageAbbreviation",
        theTranslator->trPageAbbreviation());
    
    WriteSentence(fout, "trSources",
        theTranslator->trSources());
    
    WriteSentence(fout, "trDeprecated",
        theTranslator->trDeprecated());
    
    WriteSentence(fout, "trConstructorDocumentation",
        theTranslator->trConstructorDocumentation());
    
    WriteSentence(fout, "trGotoSourceCode",
        theTranslator->trGotoSourceCode());
    
    WriteSentence(fout, "trGotoDocumentation",
        theTranslator->trGotoDocumentation());
    
    WriteSentence(fout, "trPrecondition",
        theTranslator->trPrecondition());
    
    WriteSentence(fout, "trPostcondition",
        theTranslator->trPostcondition());
    
    WriteSentence(fout, "trInvariant",
        theTranslator->trInvariant());
    
    WriteSentence(fout, "trInitialValue",
        theTranslator->trInitialValue());
    
    WriteSentence(fout, "trCode",
        theTranslator->trCode());
    
    WriteSentence(fout, "trGraphicalHierarchy",
        theTranslator->trGraphicalHierarchy());
    
    WriteSentence(fout, "trGotoGraphicalHierarchy",
        theTranslator->trGotoGraphicalHierarchy());
    
    WriteSentence(fout, "trGotoTextualHierarchy",
        theTranslator->trGotoTextualHierarchy());
    
    WriteSentence(fout, "trPageIndex",
        theTranslator->trPageIndex());
    
    WriteSentence(fout, "trNote",
        theTranslator->trNote());
    
    WriteSentence(fout, "trPublicTypes",
        theTranslator->trPublicTypes());
    
    Config_setBool(TRUE);
    WriteSentence(fout, "trPublicAttribsC",
        theTranslator->trPublicAttribs());
    
    Config_setBool(FALSE);
    WriteSentence(fout, "trPublicAttribs",
        theTranslator->trPublicAttribs());
    
    WriteSentence(fout, "trStaticPublicAttribs",
        theTranslator->trStaticPublicAttribs());
    
    WriteSentence(fout, "trProtectedTypes",
        theTranslator->trProtectedTypes());
    
    WriteSentence(fout, "trProtectedAttribs",
        theTranslator->trProtectedAttribs());
    
    WriteSentence(fout, "trStaticProtectedAttribs",
        theTranslator->trStaticProtectedAttribs());
    
    WriteSentence(fout, "trPrivateTypes",
        theTranslator->trPrivateTypes());
    
    WriteSentence(fout, "trPrivateAttribs",
        theTranslator->trPrivateAttribs());
    
    WriteSentence(fout, "trStaticPrivateAttribs",
        theTranslator->trStaticPrivateAttribs());
    
    WriteSentence(fout, "trTodo",
        theTranslator->trTodo());
    
    WriteSentence(fout, "trTodoList",
        theTranslator->trTodoList());
    
    WriteSentence(fout, "trReferencedBy",
        theTranslator->trReferencedBy());
    
    WriteSentence(fout, "trRemarks",
        theTranslator->trRemarks());
    
    WriteSentence(fout, "trAttention",
        theTranslator->trAttention());
    
    WriteSentence(fout, "trInclByDepGraph",
        theTranslator->trInclByDepGraph());
    
    WriteSentence(fout, "trSince",
        theTranslator->trSince());
    
    WriteSentence(fout, "trLegendTitle",
        theTranslator->trLegendTitle());
    
    WriteSentence(fout, "trLegendDocs",
        theTranslator->trLegendDocs());
    
    WriteSentence(fout, "trLegend",
        theTranslator->trLegend());
    
    WriteSentence(fout, "trTest",
        theTranslator->trTest());
    
    WriteSentence(fout, "trTestList",
        theTranslator->trTestList());
    
    WriteSentence(fout, "trDCOPMethods",
        theTranslator->trDCOPMethods());
    
    WriteSentence(fout, "trProperties",
        theTranslator->trProperties());
    
    WriteSentence(fout, "trPropertyDocumentation",
        theTranslator->trPropertyDocumentation());
    
    WriteSentence(fout, "trInterfaces",
        theTranslator->trInterfaces());
    
    Config_setBool(TRUE);
    WriteSentence(fout, "trClassesC",
        theTranslator->trClasses());
    
    Config_setBool(FALSE);
    WriteSentence(fout, "trClasses",
        theTranslator->trClasses());
    
    WriteSentence(fout, "trPackageList",
        theTranslator->trPackageList());
    
    WriteSentence(fout, "trPackageListDescription",
        theTranslator->trPackageListDescription());
    
    WriteSentence(fout, "trPackages",
        theTranslator->trPackages());
    
    WriteSentence(fout, "trPackageDocumentation",
        theTranslator->trPackageDocumentation());
    
    WriteSentence(fout, "trDefineValue",
        theTranslator->trDefineValue());
    
    WriteSentence(fout, "trBug",
        theTranslator->trBug());
    
    WriteSentence(fout, "trBugList",
        theTranslator->trBugList());
    
    WriteSentence(fout, "trRTFansicp",
        theTranslator->trRTFansicp());
    
    WriteSentence(fout, "trRTFCharSet",
        theTranslator->trRTFCharSet());
    
    WriteSentence(fout, "trRTFGeneralIndex",
        theTranslator->trRTFGeneralIndex());
    
    
    fout << "\n<!-- Sets of simple sentences -->\n";
    
    WriteSentence(fout, "trFileListDescriptionF",
        theTranslator->trFileListDescription(FALSE));
    WriteSentence(fout, "trFileListDescriptionT",
        theTranslator->trFileListDescription(TRUE)); 
    
    fout << "<!-- -->\n";

    Config_setBool(TRUE);
    WriteSentence(fout, "trCompoundMembersDescriptionFC",
        theTranslator->trCompoundMembersDescription(FALSE));
    WriteSentence(fout, "trCompoundMembersDescriptionTC",
        theTranslator->trCompoundMembersDescription(TRUE)); 
    
    Config_setBool(FALSE);
    WriteSentence(fout, "trCompoundMembersDescriptionF",
        theTranslator->trCompoundMembersDescription(FALSE));
    WriteSentence(fout, "trCompoundMembersDescriptionT",
        theTranslator->trCompoundMembersDescription(TRUE)); 
    
    fout << "<!-- -->\n";
    
    Config_setBool(TRUE);
    WriteSentence(fout, "trFileMembersDescriptionFC",
        theTranslator->trFileMembersDescription(FALSE));
    WriteSentence(fout, "trFileMembersDescriptionTC",
        theTranslator->trFileMembersDescription(TRUE)); 
    
    Config_setBool(FALSE);
    WriteSentence(fout, "trFileMembersDescriptionF",
        theTranslator->trFileMembersDescription(FALSE));
    WriteSentence(fout, "trFileMembersDescriptionT",
        theTranslator->trFileMembersDescription(TRUE)); 
    
    fout << "<!-- -->\n";
    
    WriteSentence(fout, "trNamespaceListDescriptionF",
        theTranslator->trNamespaceListDescription(FALSE));
    WriteSentence(fout, "trNamespaceListDescriptionT",
        theTranslator->trNamespaceListDescription(TRUE));
    
    fout << "<!-- -->\n";
    
    WriteSentence(fout, "trNamespaceMemberDescriptionF",
        theTranslator->trNamespaceMemberDescription(FALSE));
    WriteSentence(fout, "trNamespaceMemberDescriptionT",
        theTranslator->trNamespaceMemberDescription(TRUE));
    
    fout << "<!-- -->\n";
    
    WriteSentence(fout, "trclass",   theTranslator->trClass(FALSE, TRUE ));
    WriteSentence(fout, "trclasses", theTranslator->trClass(FALSE, FALSE));
    WriteSentence(fout, "trClass",   theTranslator->trClass(TRUE,  TRUE ));
    WriteSentence(fout, "trClasses", theTranslator->trClass(TRUE,  FALSE));
    
    fout << "<!-- -->\n";
    
    WriteSentence(fout, "trfile",    theTranslator->trFile(FALSE, TRUE ));
    WriteSentence(fout, "trfiles",   theTranslator->trFile(FALSE, FALSE));
    WriteSentence(fout, "trFile",    theTranslator->trFile(TRUE,  TRUE ));
    WriteSentence(fout, "trFiles",   theTranslator->trFile(TRUE,  FALSE));
    
    fout << "<!-- -->\n";
    
    WriteSentence(fout, "trnamespace",  theTranslator->trNamespace(FALSE, TRUE ));
    WriteSentence(fout, "trnamespaces", theTranslator->trNamespace(FALSE, FALSE));
    WriteSentence(fout, "trNamespace",  theTranslator->trNamespace(TRUE,  TRUE ));
    WriteSentence(fout, "trNamespaces", theTranslator->trNamespace(TRUE,  FALSE));
    
    fout << "<!-- -->\n";
    
    WriteSentence(fout, "trgroup",  theTranslator->trGroup(FALSE, TRUE ));
    WriteSentence(fout, "trgroups", theTranslator->trGroup(FALSE, FALSE));
    WriteSentence(fout, "trGroup",  theTranslator->trGroup(TRUE,  TRUE ));
    WriteSentence(fout, "trGroups", theTranslator->trGroup(TRUE,  FALSE)); 
    
    fout << "<!-- -->\n";
    
    WriteSentence(fout, "trpage",  theTranslator->trPage(FALSE, TRUE ));
    WriteSentence(fout, "trpages", theTranslator->trPage(FALSE, FALSE));
    WriteSentence(fout, "trPage",  theTranslator->trPage(TRUE,  TRUE ));
    WriteSentence(fout, "trPages", theTranslator->trPage(TRUE,  FALSE));
    
    fout << "<!-- -->\n";
    
    WriteSentence(fout, "trmember",  theTranslator->trMember(FALSE, TRUE ));
    WriteSentence(fout, "trmembers", theTranslator->trMember(FALSE, FALSE));
    WriteSentence(fout, "trMember",  theTranslator->trMember(TRUE,  TRUE ));
    WriteSentence(fout, "trMembers", theTranslator->trMember(TRUE,  FALSE));
    
    fout << "<!-- -->\n";
    
    WriteSentence(fout, "trfield",   theTranslator->trField(FALSE, TRUE ));
    WriteSentence(fout, "trfields",  theTranslator->trField(FALSE, FALSE));
    WriteSentence(fout, "trField",   theTranslator->trField(TRUE,  TRUE ));
    WriteSentence(fout, "trFields",  theTranslator->trField(TRUE,  FALSE));
    
    fout << "<!-- -->\n";
    
    WriteSentence(fout, "trglobal",  theTranslator->trGlobal(FALSE, TRUE ));
    WriteSentence(fout, "trglobals", theTranslator->trGlobal(FALSE, FALSE));
    WriteSentence(fout, "trGlobal",  theTranslator->trGlobal(TRUE,  TRUE ));
    WriteSentence(fout, "trGlobals", theTranslator->trGlobal(TRUE,  FALSE));
    
    fout << "<!-- -->\n";
    
    WriteSentence(fout, "trauthor",  theTranslator->trAuthor(FALSE, TRUE ));
    WriteSentence(fout, "trauthors", theTranslator->trAuthor(FALSE, FALSE));
    WriteSentence(fout, "trAuthor",  theTranslator->trAuthor(TRUE,  TRUE ));
    WriteSentence(fout, "trAuthors", theTranslator->trAuthor(TRUE,  FALSE));
    
    fout << "<!-- -->\n";
    
    WriteSentence(fout, "trClassDocGeneratedFromFile",
        theTranslator->trGeneratedFromFiles(ClassDef::Class, TRUE));
    WriteSentence(fout, "trClassDocGeneratedFromFiles",
        theTranslator->trGeneratedFromFiles(ClassDef::Class, FALSE));
    
    fout << "\n";
    
    WriteSentence(fout, "trStructDocGeneratedFromFile",
        theTranslator->trGeneratedFromFiles(ClassDef::Struct, TRUE));
    WriteSentence(fout, "trStructDocGeneratedFromFiles",
        theTranslator->trGeneratedFromFiles(ClassDef::Struct, FALSE)); 
    
    fout << "\n";
    
    WriteSentence(fout, "trUnionDocGeneratedFromFile",
        theTranslator->trGeneratedFromFiles(ClassDef::Union, TRUE));
    WriteSentence(fout, "trUnionDocGeneratedFromFiles",
        theTranslator->trGeneratedFromFiles(ClassDef::Union, FALSE)); 
    
    fout << "\n";
    
    WriteSentence(fout, "trInterfaceDocGeneratedFromFile",
        theTranslator->trGeneratedFromFiles(ClassDef::Interface, TRUE));
    
    WriteSentence(fout, "trInterfaceDocGeneratedFromFiles",
        theTranslator->trGeneratedFromFiles(ClassDef::Interface, FALSE));
    
    fout << "\n";
    
    WriteSentence(fout, "trExceptionDocGeneratedFromFile",
        theTranslator->trGeneratedFromFiles(ClassDef::Exception, TRUE));
    
    WriteSentence(fout, "trExceptionDocGeneratedFromFiles",
        theTranslator->trGeneratedFromFiles(ClassDef::Exception, FALSE));
    
    fout << "<!-- -->\n";
    
    
    fout << "\n------------------------------------------\n\n";
    
    fout << "\n<!-- Template sentences (or what should be) -->\n\n";
    
    WriteSentence(fout, "trDefinedAtLineInSourceFile",
        theTranslator->trDefinedAtLineInSourceFile());
    
    WriteSentence(fout, "trDefinedInSourceFile",
        theTranslator->trDefinedInSourceFile());
    
    WriteSentence(fout, "trFileReference",
        theTranslator->trFileReference("$1"));
    
    WriteSentence(fout, "trNamespaceReference",
        theTranslator->trNamespaceReference("$1"));
    
    WriteSentence(fout, "trCollaborationDiagram",
        theTranslator->trCollaborationDiagram("$1"));
    
    WriteSentence(fout, "trInclDepGraph",
        theTranslator->trInclDepGraph("$1"));
    
    WriteSentence(fout, "trPackage",
        theTranslator->trPackage("$1"));
    
    
    fout << "\n<!-- Sets of template sentences -->\n\n";
    
    WriteSentence(fout, "trClassReference",
        theTranslator->trCompoundReference("$1", ClassDef::Class, FALSE));
    
    WriteSentence(fout, "trClassTemplateReference",
        theTranslator->trCompoundReference("$1", ClassDef::Class, TRUE)); 
    
    fout << "\n";
    
    WriteSentence(fout, "trStructReference",
        theTranslator->trCompoundReference("$1", ClassDef::Struct, FALSE));
    
    WriteSentence(fout, "trUnionReference",
        theTranslator->trCompoundReference("$1", ClassDef::Union, FALSE));
    
    WriteSentence(fout, "trInterfaceReference",
        theTranslator->trCompoundReference("$1", ClassDef::Interface, FALSE));
    
    WriteSentence(fout, "trExceptionReference",
        theTranslator->trCompoundReference("$1", ClassDef::Exception, FALSE));
    
    fout << "\n<!-- Simple sentences with fixed-name generated-sentence "
            "references inside\n\n";
    
    WriteSentence(fout, "trGeneratedAutomatically",
        theTranslator->trGeneratedAutomatically("&ProjName;"));
    
    WriteSentence(fout, "trGeneratedAt",
        theTranslator->trGeneratedAt("&GenDate;", "&ProjName;"));
    
    fout << "-->\n\n"
            "<!-- ... but they can be also implemented as "
            "template sentences)-->\n\n";
    
    WriteSentence(fout, "trGeneratedAutomatically",
        theTranslator->trGeneratedAutomatically("$1"));
    
    WriteSentence(fout, "trGeneratedAt",
        theTranslator->trGeneratedAt("$1", "$2"));
    
    fout << "\n<!-- Simple fragments that should be converted "
            "to template sentences -->\n\n";
        
        WriteSentence(fout, "trThisIsTheListOfAllMembers",
        theTranslator->trThisIsTheListOfAllMembers());
    
    WriteSentence(fout, "trIncludingInheritedMembers",
        theTranslator->trIncludingInheritedMembers());
    
    fout << "\n<!-- should be converted to something like... -->\n\n";
    
    WriteSentence(fout, "trThisIsTheListOfAllMembers",
        theTranslator->trThisIsTheListOfAllMembers() + "$1.");
    
    WriteSentence(fout, "trTheListOfAllMembersIncludingInherited",
        theTranslator->trThisIsTheListOfAllMembers() + "$1"
        + theTranslator->trIncludingInheritedMembers());
    
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
    s.replace(pos, 2, "$1");

    WriteSentence(fout, "trInherits", s);
                      
    s = theTranslator->trInheritsList(2);
    pos = s.find("@0");
    std::string::size_type pos2 = s.find("@1");
    s.replace(pos, pos2-pos+2, "$1");

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
    s.replace(pos, 2, "$1");

    WriteSentence(fout, "trInheritedBy", s);
                      
    s = theTranslator->trInheritedByList(2);
    pos = s.find("@0");
    pos2 = s.find("@1");
    s.replace(pos, pos2-pos+2, "$1");

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
    s.replace(pos, 2, "$1");

    WriteSentence(fout, "trReimplementedFrom", s);
                      
    s = theTranslator->trReimplementedFromList(2);
    pos = s.find("@0");
    pos2 = s.find("@1");
    s.replace(pos, pos2-pos+2, "$1");

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
    s.replace(pos, 2, "$1");

    WriteSentence(fout, "trReimplementedIn", s);
                      
    s = theTranslator->trReimplementedInList(2);
    pos = s.find("@0");
    pos2 = s.find("@1");
    s.replace(pos, pos2-pos+2, "$1");

    WriteSentence(fout, "trReimplementedInList", s);
    //-----------------------------------------------------------------
    
    fout << "\n<!-- (end) -->\n";
    
    // Close the output file.
    //
    fout.close();

    std::cerr << "\n";
}


int main()
{
	GenerateTranslatorSentences("english");
	GenerateTranslatorSentences("german");
	GenerateTranslatorSentences("czech");
	GenerateTranslatorSentences("dutch");

	return 0;
}
