# Измерение характеристик кэшей процессора

Экспериментальное измерение размера кэшей разных уровней, времени последовательного и случайного доступа к ним.

# Отчет

Эксперимент проводился на intel core 2 duo p7450:

**$lscpu**
* L1d cache 32KB
* Li cache 32KB
* L2 cache 3072KB

Графики отображают время одного обращения к кэшу в зависимости от объма занимаемой памяти списком, по которуму происходит итерация.
* Зеленый - последовательный доступ.
* Синий - случайный доступ.

## График №1

![Alt text](https://github.com/streambuf/cache_latency/blob/master/screenshots/1.png "")

Видно, как резко возрастает время обращения к cache после 30KB, из этого следует, что процессор начал обращаться уже к L2 cache.
Таким образом, экспериментально удалось выяснить, что размер L1 = 30KB. Приблизительно такое же значения и в спецификации (L1 cache 32KB)

## График №2

Видно, как резко возрастает время обращения к cache после 3000KB, из этого следует, что процессор начал обращаться уже к оперативной памяти.
Таким образом, экспериментально удалось выяснить, что размер L2 = 3000KB. Приблизительно такое же значения и в спецификации (L2 cache 3072KB)

![Alt text](https://github.com/streambuf/cache_latency/blob/master/screenshots/2.png "")

## График №3

Здесь показано как менялось время при размере списка от 1КБ до 5МБ

![Alt text](https://github.com/streambuf/cache_latency/blob/master/screenshots/3.png "")
