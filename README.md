# Библиотека для записи сообщений в журнал с разными уровнями важности

## Часть 1

_Библиотека для записи текстовых сообщений в журнал. В качестве журнала используется файл с расширением .txt_

Библиотека выполняет следующие требования:

1. Библиотека является динамической
2. Библиотека при инициализации принимает следующие параметры:
   
   2.1 Имя файла журнала
   
   2.2 Уровень важности сообщения по умолчанию. Сообщения с уровнем ниже заданного не записываются в журнал. Уровень задаётся с помощью перечисления с понятными именами. Три уровня важности: __0 - LOW__, __1 - MEDIUM__ и __2 - HIGH__.
3. В журнале сохраняется следующая информация: _текст сообщения_, _уровень важности_ и _время получения сообщения_.
4. После инициализации есть возможность менять уровень важности сообщений по умолчанию.

## Часть 2

_Консольное многопоточное приложение для проверки библиотеки записи сообщений в журнал_

Приложение выполняет следующие требования:

1. Подключает и использует библиотеку, реализованную в Части 1, для записи сообщений в журнал.
2. В консоли принимает от пользователя сообщение и его уровень важности. Уровень важности может отсутствовать.
3. Передаёт принятые данные от пользователя в отдельный поток для записи в журнал. Передача данных является потокобезопасной.
4. Ожидает нового ввода от пользователя после передачи данных.
5. Параметрами приложения являются имя файла журнала и уровень важности сообщения по умолчанию.

## Сборка библиотеки

1. Перед началом работы убедитесь, что у вас установлен g++ и Make.
2. Выполните команду для сборки библиотеки:
   ```make
   make build
   ```
3. Далее выполните команду для запуска консольного приложения:
   ```make
   make run ARGS="<log_filename> [default_priority]"
   ```
4. Чтобы очистить проект от всех временных файлов выполните команду:
   ```make
   make clean
   ```

## Работа с приложением

1. При запуске консольного приложения сначала нужно ввести текст сообщения:
![image](https://github.com/user-attachments/assets/501c5c1a-a170-4b95-a211-ea0d5255bb45)
2. Далее нужно ввести уровень важности сообщения:
![image](https://github.com/user-attachments/assets/64c0918d-cd7e-43e1-b59b-752f6d31e87a)

После этого запись запишется в файл .txt с временем записи.
