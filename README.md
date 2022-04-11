### Программа Anonymous MAPF
 * Чтобы построить маршрут, запускаем main.cpp с двумя аргументами: 1 - путь к карте, 2 - путь куда записывать результат
 * Чтобы сделать визуализацию, запускаем visualizer/main.py с двумя аргументами: 1 - путь с построенным маршрутом, 2 - путь куда сохранять визуализацию
 * Пример:
   * main.cpp ../examples/example3.xml ../examples/log3.xml
   * main.py ../examples/log3.xml ../examples/visualization3.gif
 * В examples есть готовые карты с визуализацией

## Время работы:
 * Поле 100х100 с 2 агентами 500 секунд
 * Поле 32x32 с 10 агентами 13 секунд
 * Поле 32x32 с 20 агентами 14 секунд
 * Поле 32x32 с 40 агентами 26 секунд