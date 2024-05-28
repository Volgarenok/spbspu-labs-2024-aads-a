#include "comlinearg.hpp"
#include "commands.hpp"

void piyavkin::help(std::ostream& out)
{
  out << "Система команд\n";
  out << "1. adddictionary <dictionary name>\n";
  out << "Создать объект с именем <dictionary name>. Если объект с таким именем уже существует,";
  out << " то вывести сообщение <INVALID COMMAND>\n";
  out << "2. changedictionary <dictionary name> <key> <value>\n";
  out << "Изменение словаря. Если ключ существует в словаре, то изменить его значение на <value>,";
  out << " иначе добавить новый <key>";
  out << " с значением <value>\n 3. makedictionary <dictionary name> <file.txt>\n";
  out << "Построить словарь по текстовому файлу. Если словарь с таким именем существует,";
  out << " то перезаписать словарь.";
  out << " Если тестового файла не существует или он не указан, то вывести сообщение <INVALID COMMAND>\n";
  out << "4. topfreq <dictionary name> <n>\nВывести топ n часто встречающихся значений,";
  out << " то есть value с наибольшим key,";
  out << " если n больше размера словаря или такого словаря не существует, то вывести сообщение";
  out << " <INVALID COMMAND>\n";
  out << "5. intersectdictionaries <new dictionary name> <dictionary name1> <dictionary name2>\n";
  out << "Найти пересечение словарей. Сохранить все совпадающие ключи, а также минимальное";
  out << " значение из них в";
  out << " <new dictionary name>. Если словарей с таким именем нет, то вывести сообщение";
  out << " <INVALID COMMAND>\n";
  out << "6. uniondictionaries <new dictionary name> <dictionary name1> <dictionary name2>\n";
  out << "Найти объединения словарей. Сохранить объединения словарей, то есть все уникальные ключи и их";
  out << " максимальное";
  out << " значение из двух словарей в <new dictionary name>. Если словарей с таким именем нет,";
  out << " то вывести сообщение";
  out << " <INVALID COMMAND>\n7. uniquedictionaries <new dictionary name> <dictionary name1>";
  out << " <dictionary name2>";
  out << "Найти и сохранить в <new dictionary name> все ключи, которые есть в <dictionary name1>,";
  out << " но которых нет в";
  out << " <dictionary name2>, и их значения. Если словарей с таким именем нет, то вывести сообщение";
  out << " <INVALID COMMAND>\n";
  out << "8. adddictionarytodictionary <dictionary name1> <dictionary name2>\nДобавить к";
  out << " <dictionary name1> все";
  out << " недостающие ключи и их значения, если ключ есть в обоих словарях, то должно быть выбрано";
  out << " максимальное значение.";
  out << " Если словарей с таким именем нет, то вывести сообщение <INVALID COMMAND>\n9. ";
  out << "subdictionarytodictionary";
  out << " <dictionary name1> <dictionary name2>\nВычесть из <dictionary name1> <dictionary name2>,";
  out << " то есть вычесть";
  out << " из значений ключей <dictionary name1>значений ключей <dictionary name2>(ключи должны совпадать,";
  out << " если разность";
  out << " получается отрицательной, то вычеркнуть ключ из <dictionary name1>\n10. printdictionary";
  out << " <dictionary name>";
  out << " <file.txt>\nЗаписать словарь в текcтовый файл, то есть вывести на каждой строке ключ - ";
  out << "значение.";
  out << " Если словаря не существует, то вывести сообщение <INVALID COMMAND>. Если файла существует,";
  out << " то вывести сообщение <INVALID COMMAND>.\n";
}

void piyavkin::check(std::istream& in, std::ostream& out, dic_t& dicts)
{
  try
  {
    makeDict(in, dicts);
    out << "GOOD FILE\n";
  }
  catch (...)
  {
    out << "BAD FILE\n";
  }
}
