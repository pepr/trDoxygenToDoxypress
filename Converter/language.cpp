// stub for the converter

//#include "message.h"
//#include "config.h"
//#include "util.h"
#include "language.h"
//#include "lang_cfg.h"
#include "translator.h"

#include "translator_en.h"
#include "translator_adapter.h"

#include "translator_de.h"
#include "translator_cz.h"

// #include "translator_nl.h"
// #include "translator_am.h"
// #include "translator_sv.h"
// #include "translator_fr.h"
// #include "translator_id.h"
// #include "translator_it.h"
// #include "translator_jp.h"
// #include "translator_je.h"
// #include "translator_es.h"
// #include "translator_eo.h"
// #include "translator_fi.h"
// #include "translator_ru.h"
// #include "translator_hr.h"
// #include "translator_pl.h"
// #include "translator_pt.h"
// #include "translator_hu.h"
// #include "translator_ke.h"
// #include "translator_kr.h"
// #include "translator_ro.h"
// #include "translator_si.h"
// #include "translator_cn.h"
// #include "translator_tw.h"
// #include "translator_no.h"
// #include "translator_br.h"
// #include "translator_dk.h"
// #include "translator_sk.h"
// #include "translator_ua.h"
// #include "translator_gr.h"
// #include "translator_sr.h"
// #include "translator_ca.h"
// #include "translator_lt.h"
// #include "translator_lv.h"
// #include "translator_za.h"
// #include "translator_ar.h"
// #include "translator_fa.h"
// #include "translator_mk.h"
// #include "translator_sc.h"
// #include "translator_vi.h"
// #include "translator_tr.h"


#define L_EQUAL(a) (langName == a)

Translator *theTranslator=0;

bool setTranslator(const std::string & langName)
{
  if (L_EQUAL("english"))
  {
      theTranslator=new TranslatorEnglish;
  }
  else if (L_EQUAL("czech"))
  {
      theTranslator = new TranslatorCzech;
  }
  else if (L_EQUAL("german"))
  {
      theTranslator = new TranslatorGerman;
  }

#ifdef LANG_NL
  else if (L_EQUAL("dutch"))
  {
    theTranslator=new TranslatorDutch;
  }
#endif
#ifdef LANG_AM
  else if (L_EQUAL("armenian"))
  {
    theTranslator=new TranslatorArmenian;
  }
#endif
#ifdef LANG_SV
  else if (L_EQUAL("swedish"))
  {
    theTranslator=new TranslatorSwedish;
  }
#endif
#ifdef LANG_FR
  else if (L_EQUAL("french"))
  {
    theTranslator=new TranslatorFrench;
  }
#endif
#ifdef LANG_ID
  else if (L_EQUAL("indonesian"))
  {
    theTranslator=new TranslatorIndonesian;
  }
#endif
#ifdef LANG_IT
  else if (L_EQUAL("italian"))
  {
    theTranslator=new TranslatorItalian;
  }
#endif
#ifdef LANG_JP
  else if (L_EQUAL("japanese"))
  {
    theTranslator=new TranslatorJapanese;
  }
#endif
#ifdef LANG_JE
  else if (L_EQUAL("japanese-en"))
  {
    theTranslator=new TranslatorJapaneseEn;
  }
#endif
#ifdef LANG_ES
  else if (L_EQUAL("spanish"))
  {
    theTranslator=new TranslatorSpanish;
  }
#endif
#ifdef LANG_FI
  else if (L_EQUAL("finnish"))
  {
    theTranslator=new TranslatorFinnish;
  }
#endif
#ifdef LANG_RU
  else if (L_EQUAL("russian"))
  {
    theTranslator=new TranslatorRussian;
  }
#endif
#ifdef LANG_HR
  else if (L_EQUAL("croatian"))
  {
    theTranslator=new TranslatorCroatian;
  }
#endif
#ifdef LANG_PL
  else if (L_EQUAL("polish"))
  {
    theTranslator=new TranslatorPolish;
  }
#endif
#ifdef LANG_PT
  else if (L_EQUAL("portuguese"))
  {
    theTranslator=new TranslatorPortuguese;
  }
#endif
#ifdef LANG_HU
  else if (L_EQUAL("hungarian"))
  {
    theTranslator=new TranslatorHungarian;
  }
#endif
#ifdef LANG_KR
  else if (L_EQUAL("korean"))
  {
    theTranslator=new TranslatorKorean;
  }
#endif
#ifdef LANG_KE
  else if (L_EQUAL("korean-en"))
  {
    theTranslator=new TranslatorKoreanEn;
  }
#endif
#ifdef LANG_RO
  else if (L_EQUAL("romanian"))
  {
    theTranslator=new TranslatorRomanian;
  }
#endif
#ifdef LANG_SI
  else if (L_EQUAL("slovene"))
  {
    theTranslator=new TranslatorSlovene;
  }
#endif
#ifdef LANG_CN
  else if (L_EQUAL("chinese"))
  {
    theTranslator=new TranslatorChinese;
  }
#endif
#ifdef LANG_TW
  else if (L_EQUAL("chinese-traditional"))
  {
    theTranslator=new TranslatorChinesetraditional;
  }
#endif
#ifdef LANG_NO
  else if (L_EQUAL("norwegian"))
  {
    theTranslator=new TranslatorNorwegian;
  }
#endif
#ifdef LANG_BR
  else if (L_EQUAL("brazilian"))
  {
    theTranslator=new TranslatorBrazilian;
  }
#endif
#ifdef LANG_DK
  else if (L_EQUAL("danish"))
  {
    theTranslator=new TranslatorDanish;
  }
#endif
#ifdef LANG_SK
  else if (L_EQUAL("slovak"))
  {
    theTranslator=new TranslatorSlovak;
  }
#endif
#ifdef LANG_UA
  else if (L_EQUAL("ukrainian"))
  {
    theTranslator=new TranslatorUkrainian;
  }
#endif
#ifdef LANG_GR
  else if (L_EQUAL("greek"))
  {
    theTranslator=new TranslatorGreek;
  }
#endif
#ifdef LANG_SR
  else if (L_EQUAL("serbian"))
  {
    theTranslator=new TranslatorSerbian;
  }
#endif
#ifdef LANG_SC
  else if (L_EQUAL("serbian-cyrillic") || L_EQUAL("serbiancyr")) /* serbiancyr for consistency with older versions */
  {
    theTranslator=new TranslatorSerbianCyrillic;
  }
#endif
#ifdef LANG_CA
  else if (L_EQUAL("catalan"))
  {
    theTranslator=new TranslatorCatalan;
  }
#endif
#ifdef LANG_LT
  else if (L_EQUAL("lithuanian"))
  {
    theTranslator=new TranslatorLithuanian;
  }
#endif
#ifdef LANG_LV
  else if (L_EQUAL("latvian"))
  {
    theTranslator=new TranslatorLatvian;
  }
#endif
#ifdef LANG_ZA
  else if (L_EQUAL("afrikaans"))
  {
    theTranslator=new TranslatorAfrikaans;
  }
#endif
#ifdef LANG_AR
  else if (L_EQUAL("arabic"))
  {
    theTranslator=new TranslatorArabic;
  }
#endif
#ifdef LANG_FA
  else if (L_EQUAL("persian") || L_EQUAL("farsi"))
  {
    theTranslator=new TranslatorPersian;
  }
#endif
#ifdef LANG_MK
  else if (L_EQUAL("macedonian"))
  {
    theTranslator=new TranslatorMacedonian;
  }
#endif
#ifdef LANG_VI
  else if (L_EQUAL("vietnamese"))
  {
    theTranslator=new TranslatorVietnamese;
  }
#endif
#ifdef LANG_TR
  else if (L_EQUAL("turkish"))
  {
    theTranslator=new TranslatorTurkish;
  }
#endif
#ifdef LANG_EO
  else if (L_EQUAL("esperanto"))
  {
    theTranslator=new TranslatorEsperanto;
  }
#endif
  else // use the default language (i.e. english)
  {
    theTranslator=new TranslatorEnglish;
    return false;
  }

  return true;
}
