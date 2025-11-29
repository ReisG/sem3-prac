Два имени файла
Если это пути к одному и тому же файлу напе

одни - символическая ссылка на другой
оба симв на третий файл
либо они являются жесткими ссылками на другой

st_ino == ___&& st_dev == __

solution
stat(name1, &buf1)
stat(name2, &buf2)
if (buf1.st_ino == buf2.st_ino && buf1.st_dev == buf2.st_dev) // the point to the same location
