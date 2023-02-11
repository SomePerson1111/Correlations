1) extractor.exe \[input_foolder\] \[output_file\]: сбор информации в \[output_file\] из всех файлов с расширением .wotreplays из папки \[input_foolder\]. 
Если параметры не указаы, используется текущая папка и файл replayinfo.txt

2) filter.exe "replayinfo.txt" \[dmg или win\] \[название машины\]: вынимает столбец значений и сохраняет в data.txt. (можно сделать в excel)

3) correlator \[input_file\]: считает автокорреляционную функцию чисел из  \[input_file\] в results.txt.

4) rand_events \[iter_num\] \[epoch_num\] \[gen_file\]: выдает \[epoch_num\] раз среднее значение \[iter_num\] случайных величин,
распределение которых задано в \[gen_file\]: текстовый файл, первый столбец которого --- частоты вападения значения, второй --- значения.
