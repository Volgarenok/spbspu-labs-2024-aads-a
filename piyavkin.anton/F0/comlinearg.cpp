#include "comlinearg.hpp"
#include "commands.hpp"

void piyavkin::help(std::ostream& out)
{
  out << "Система команд\n\n";
  out << "1. adddictionary <dictionary name>\n\n";
  out << "Создать объект с именем <dictionary name>. Если объект с таким именем уже существует,\n";
  out << " то вывести сообщение <INVALID COMMAND>\n\n";
  out << "2. changedictionary <dictionary name> <key> <value>\n";
  out << "Изменение словаря. Если ключ существует в словаре, то изменить его значение на <value>,\n";
  out << " иначе добавить новый <key>\n";
  out << " с значением <value>\n 3. makedictionary <dictionary name> <file.txt>\n\n";
  out << "Построить словарь по текстовому файлу. Если словарь с таким именем существует,\n";
  out << " то перезаписать словарь.\n";
  out << " Если тестового файла не существует или он не указан, то вывести сообщение <INVALID COMMAND>\n\n";
  out << "4. topfreq <dictionary name> <n>\nВывести топ n часто встречающихся значений,\n";
  out << " то есть value с наибольшим key,\n";
  out << " если n больше размера словаря или такого словаря не существует, то вывести сообщение\n";
  out << " <INVALID COMMAND>\n\n";
  out << "5. intersectdictionaries <new dictionary name> <dictionary name1> <dictionary name2>\n\n";
  out << "Найти пересечение словарей. Сохранить все совпадающие ключи, а также минимальное\n";
  out << " значение из них в\n";
  out << " <new dictionary name>. Если словарей с таким именем нет, то вывести сообщение\n";
  out << " <INVALID COMMAND>\n\n";
  out << "6. uniondictionaries <new dictionary name> <dictionary name1> <dictionary name2>\n\n";
  out << "Найти объединения словарей. Сохранить объединения словарей, то есть все уникальные ключи и их\n";
  out << " максимальное\n";
  out << " значение из двух словарей в <new dictionary name>. Если словарей с таким именем нет,\n";
  out << " то вывести сообщение\n";
  out << " <INVALID COMMAND>\n7. uniquedictionaries <new dictionary name> <dictionary name1>\n";
  out << " <dictionary name2>\n";
  out << "Найти и сохранить в <new dictionary name> все ключи, которые есть в <dictionary name1>,\n";
  out << " но которых нет в\n";
  out << " <dictionary name2>, и их значения. Если словарей с таким именем нет, то вывести сообщение\n";
  out << " <INVALID COMMAND>\n\n";
  out << "8. adddictionarytodictionary <dictionary name1> <dictionary name2>\nДобавить к\n";
  out << " <dictionary name1> все\n";
  out << " недостающие ключи и их значения, если ключ есть в обоих словарях, то должно быть выбрано\n";
  out << " максимальное значение.\n";
  out << " Если словарей с таким именем нет, то вывести сообщение <INVALID COMMAND>\n9. \n";
  out << "subdictionarytodictionary\n";
  out << " <dictionary name1> <dictionary name2>\nВычесть из <dictionary name1> <dictionary name2>,\n";
  out << " то есть вычесть\n";
  out << " из значений ключей <dictionary name1>значений ключей <dictionary name2>(ключи должны совпадать,\n";
  out << " если разность\n";
  out << " получается отрицательной, то вычеркнуть ключ из <dictionary name1>\n10. printdictionary\n";
  out << " <dictionary name>\n\n";
  out << " <file.txt>\nЗаписать словарь в текcтовый файл, то есть вывести на каждой строке ключ - \n";
  out << "значение.\n";
  out << " Если словаря не существует, то вывести сообщение <INVALID COMMAND>. Если файла существует,\n";
  out << " то вывести сообщение <INVALID COMMAND>.\n\n";
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
