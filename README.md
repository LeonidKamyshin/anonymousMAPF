### Программа Anonymous MAPF


#### Запуск через командную строку:
* Чтобы построить маршрут, запускаем main.cpp с двумя аргументами: 1 - путь к карте, 2 - путь куда записывать результат

* Чтобы сделать визуализацию, запускаем visualizer/main.py с двумя аргументами: 1 - путь с построенным маршрутом, 2 - путь куда сохранять визуализацию
* Пример:
  * main.cpp ../examples/example3.xml ../examples/log3.xml
  * python visualizer/main.py ../examples/log3.xml ../examples/visualization3.gif

Перед запуском визуализатора надо прописать команду pip install -r visualizer/requirements.txt
#### В examples есть готовые карты с визуализацией 