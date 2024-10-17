-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Хост: 10.0.7.170
-- Время создания: Сен 22 2023 г., 13:03
-- Версия сервера: 8.0.20-11
-- Версия PHP: 7.4.33

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- База данных: `edu_220392_`
--

-- --------------------------------------------------------

--
-- Структура таблицы `food diary`
--

CREATE TABLE `food diary` (
  `Дата` date NOT NULL,
  `Калории` int NOT NULL,
  `Белки` int NOT NULL,
  `Жиры` int NOT NULL,
  `Углводы` int NOT NULL,
  `Вес` int NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Дамп данных таблицы `food diary`
--

INSERT INTO `food diary` (`Дата`, `Калории`, `Белки`, `Жиры`, `Углводы`, `Вес`) VALUES
('2023-09-22', 5, 5, 5, 5, 55);

-- --------------------------------------------------------

--
-- Структура таблицы `Products`
--

CREATE TABLE `Products` (
  `Id` int NOT NULL,
  `Название` varchar(100) NOT NULL,
  `Калории` int NOT NULL,
  `Белки` int NOT NULL,
  `Жиры` int NOT NULL,
  `Углеводы` int NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Дамп данных таблицы `Products`
--

INSERT INTO `Products` (`Id`, `Название`, `Калории`, `Белки`, `Жиры`, `Углеводы`) VALUES
(1, 'Яйцо куриное', 157, 13, 11, 1),
(2, 'Баклажан', 24, 1, 0, 5),
(3, 'Кабачок', 24, 1, 0, 5),
(4, 'Томат (помидор)', 20, 1, 0, 4),
(5, 'Молоко 1,5%', 45, 3, 2, 5),
(6, 'Сыр \"Пармезан\"', 392, 36, 26, 1),
(7, 'Оладьи', 213, 7, 7, 32),
(8, 'Арахис', 552, 26, 45, 10),
(9, 'Морковь', 35, 1, 0, 7),
(10, 'Огурец', 14, 1, 0, 3),
(11, 'Тыква', 22, 1, 0, 4),
(12, 'Банан		', 96, 2, 1, 21),
(13, 'Колбаски охотничьи', 463, 25, 40, 0),
(14, 'Яблоки', 47, 0, 0, 10),
(15, 'Абрикос', 44, 1, 0, 9);

--
-- Индексы сохранённых таблиц
--

--
-- Индексы таблицы `food diary`
--
ALTER TABLE `food diary`
  ADD PRIMARY KEY (`Дата`);

--
-- Индексы таблицы `Products`
--
ALTER TABLE `Products`
  ADD PRIMARY KEY (`Id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
