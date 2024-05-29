#include "comlinearg.hpp"
#include "commands.hpp"

void piyavkin::help(std::ostream& out)
{
  out << "Система команд\n" << '\n'
      << "1. adddictionary <dictionary name>\n" << '\n'
      << "Создать объект с именем <dictionary name>. Если объект с таким именем уже существует," << '\n'
      << " то вывести сообщение <INVALID COMMAND>\n" << '\n'
      << "2. changedictionary <dictionary name> <key> <value>" << '\n'
      << "Изменение словаря. Если ключ существует в словаре, то изменить его значение на <value>," << '\n'
      << " иначе добавить новый <key>" << '\n'
      << " с значением <value>\n 3. makedictionary <dictionary name> <file.txt>\n" << '\n'
      << "Построить словарь по текстовому файлу. Если словарь с таким именем существует,\n"
      << " то перезаписать словарь." << '\n'
      << " Если тестового файла не существует или он не указан, то вывести сообщение <INVALID COMMAND>\n" << '\n'
      << "4. topfreq <dictionary name> <n>\nВывести топ n часто встречающихся значений," << '\n'
      << " то есть value с наибольшим key," << '\n'
      << " если n больше размера словаря или такого словаря не существует, то вывести сообщение" << '\n'
      << " <INVALID COMMAND>\n" << '\n'
      << "5. intersectdictionaries <new dictionary name> <dictionary name1> <dictionary name2>\n" << '\n'
      << "Найти пересечение словарей. Сохранить все совпадающие ключи, а также минимальное" << '\n'
      << " значение из них в" << '\n'
      << " <new dictionary name>. Если словарей с таким именем нет, то вывести сообщение" << '\n'
      << " <INVALID COMMAND>\n" << '\n'
      << "6. uniondictionaries <new dictionary name> <dictionary name1> <dictionary name2>\n" << '\n'
      << "Найти объединения словарей. Сохранить объединения словарей, то есть все уникальные ключи и их" << '\n'
      << " максимальное" << '\n'
      << " значение из двух словарей в <new dictionary name>. Если словарей с таким именем нет," << '\n'
      << " то вывести сообщение" << '\n'
      << " <INVALID COMMAND>\n7. uniquedictionaries <new dictionary name> <dictionary name1>" << '\n'
      << " <dictionary name2>" << '\n'
      << "Найти и сохранить в <new dictionary name> все ключи, которые есть в <dictionary name1>," << '\n'
      << " но которых нет в" << '\n'
      << " <dictionary name2>, и их значения. Если словарей с таким именем нет, то вывести сообщение" << '\n'
      << " <INVALID COMMAND>\n" << '\n'
      << "8. adddictionarytodictionary <dictionary name1> <dictionary name2>\nДобавить к" << '\n'
      << " <dictionary name1> все" << '\n'
      << " недостающие ключи и их значения, если ключ есть в обоих словарях, то должно быть выбрано" << '\n'
      << " максимальное значение." << '\n'
      << " Если словарей с таким именем нет, то вывести сообщение <INVALID COMMAND>\n9. " << '\n'
      << "subdictionarytodictionary" << '\n'
      << " <dictionary name1> <dictionary name2>\nВычесть из <dictionary name1> <dictionary name2>," << '\n'
      << " то есть вычесть" << '\n'
      << " из значений ключей <dictionary name1>значений ключей <dictionary name2>(ключи должны совпадать," << '\n'
      << " если разность" << '\n'
      << " получается отрицательной, то вычеркнуть ключ из <dictionary name1>\n10. printdictionary" << '\n'
      << " <dictionary name>\n" << '\n'
      << " <file.txt>\nЗаписать словарь в текcтовый файл, то есть вывести на каждой строке ключ - " << '\n'
      << "значение." << '\n'
      << " Если словаря не существует, то вывести сообщение <INVALID COMMAND>. Если файла существует," << '\n'
      << " то вывести сообщение <INVALID COMMAND>.\n\n";
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
