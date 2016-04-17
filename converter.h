#ifndef CONVERTER_H
#define CONVERTER_H

class QCString;
class QTextStream;

void GenerateAllTranslatorSentences();
void WriteHeading(QTextStream & fout,
                  const QCString & CountryName,
                  const QCString & CharsetId);
void WriteSentence(QTextStream & fout,
                   const QCString & SentenceId,
                   const QCString & SentenceBody);
void GenerateTranslatorSentences(const QCString & sLang);

#endif

