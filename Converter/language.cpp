// stub for the converter

#define FALSE false
#define TRUE true

#include "language.h"
#include "translator.h"

#include "translator_en.h"
#include "translator_adapter.h"

#include "translator_de.h"
#include "translator_cz.h"

#include "translator_nl.h"
#include "translator_am.h"
#include "translator_sv.h"
#include "translator_fr.h"
#include "translator_id.h"
#include "translator_it.h"
//#include "translator_jp.h"
#include "translator_je.h"
#include "translator_es.h"
#include "translator_eo.h"
#include "translator_fi.h"
#include "translator_ru.h"
#include "translator_hr.h"
#include "translator_pl.h"
#include "translator_pt.h"
#include "translator_hu.h"
#include "translator_ke.h"
#include "translator_kr.h"
#include "translator_ro.h"
#include "translator_si.h"
#include "translator_cn.h"
#include "translator_tw.h"
#include "translator_no.h"
#include "translator_br.h"
#include "translator_dk.h"
//#include "translator_sk.h"
#include "translator_ua.h"
#include "translator_gr.h"
#include "translator_sr.h"
#include "translator_ca.h"
#include "translator_lt.h"
#include "translator_lv.h"
#include "translator_za.h"
#include "translator_ar.h"
#include "translator_fa.h"
#include "translator_mk.h"
#include "translator_sc.h"
#include "translator_vi.h"
#include "translator_tr.h"


#define L_EQUAL(a) (langName == a)

Translator *theTranslator{ nullptr };

bool setTranslator(const std::string & langName)
{
    // If the translator object exists, delete it. New one will
    // be created immediately.
    if (theTranslator != nullptr)
    {
        delete theTranslator;
        theTranslator = nullptr;
    }

    if (L_EQUAL("english")) { theTranslator = new TranslatorEnglish; }
    else if (L_EQUAL("czech")) { theTranslator = new TranslatorCzech; }
    else if (L_EQUAL("german")) { theTranslator = new TranslatorGerman; }
    else if (L_EQUAL("dutch")) { theTranslator = new TranslatorDutch; }
    else if (L_EQUAL("armenian")) { theTranslator = new TranslatorArmenian; }
    else if (L_EQUAL("swedish")) { theTranslator = new TranslatorSwedish; }
    else if (L_EQUAL("french")) { theTranslator = new TranslatorFrench; }
    else if (L_EQUAL("indonesian")) { theTranslator = new TranslatorIndonesian; }
    else if (L_EQUAL("italian")) { theTranslator = new TranslatorItalian; }
    //else if (L_EQUAL("japanese")) { theTranslator = new TranslatorJapanese; }
    else if (L_EQUAL("japanese-en")) { theTranslator = new TranslatorJapaneseEn; }
    else if (L_EQUAL("spanish")) { theTranslator = new TranslatorSpanish; }
    else if (L_EQUAL("finnish")) { theTranslator = new TranslatorFinnish; }
    else if (L_EQUAL("russian")) { theTranslator = new TranslatorRussian; }
    else if (L_EQUAL("croatian")) { theTranslator = new TranslatorCroatian; }
    else if (L_EQUAL("polish")) { theTranslator = new TranslatorPolish; }
    else if (L_EQUAL("portuguese")) { theTranslator = new TranslatorPortuguese; }
    else if (L_EQUAL("hungarian")) { theTranslator = new TranslatorHungarian; }
    else if (L_EQUAL("korean")) { theTranslator = new TranslatorKorean; }
    else if (L_EQUAL("korean-en")) { theTranslator = new TranslatorKoreanEn; }
    else if (L_EQUAL("romanian")) { theTranslator = new TranslatorRomanian; }
    else if (L_EQUAL("slovene")) { theTranslator = new TranslatorSlovene; }
    else if (L_EQUAL("chinese")) { theTranslator = new TranslatorChinese; }
    else if (L_EQUAL("chinese-traditional")) { theTranslator = new TranslatorChinesetraditional; }
    else if (L_EQUAL("norwegian")) { theTranslator = new TranslatorNorwegian; }
    else if (L_EQUAL("brazilian")) { theTranslator = new TranslatorBrazilian; }
    else if (L_EQUAL("danish")) { theTranslator = new TranslatorDanish; }
    //else if (L_EQUAL("slovak")) { theTranslator = new TranslatorSlovak; }
    else if (L_EQUAL("ukrainian")) { theTranslator = new TranslatorUkrainian; }
    else if (L_EQUAL("greek")) { theTranslator = new TranslatorGreek; }
    else if (L_EQUAL("serbian")) { theTranslator = new TranslatorSerbian; }
    /* serbiancyr for consistency with older versions */
    else if (L_EQUAL("serbian-cyrillic") || L_EQUAL("serbiancyr")) { theTranslator = new TranslatorSerbianCyrillic; }
    else if (L_EQUAL("catalan")) { theTranslator = new TranslatorCatalan; }
    else if (L_EQUAL("lithuanian")) { theTranslator = new TranslatorLithuanian; }
    else if (L_EQUAL("latvian")) { theTranslator = new TranslatorLatvian; }
    else if (L_EQUAL("afrikaans")) { theTranslator = new TranslatorAfrikaans; }
    else if (L_EQUAL("arabic")) { theTranslator = new TranslatorArabic; }
    else if (L_EQUAL("persian") || L_EQUAL("farsi")) { theTranslator = new TranslatorPersian; }
    else if (L_EQUAL("macedonian")) { theTranslator = new TranslatorMacedonian; }
    else if (L_EQUAL("vietnamese")) { theTranslator = new TranslatorVietnamese; }
    else if (L_EQUAL("turkish")) { theTranslator = new TranslatorTurkish; }
    else if (L_EQUAL("esperanto")) { theTranslator = new TranslatorEsperanto; }

    return theTranslator != nullptr;
}
