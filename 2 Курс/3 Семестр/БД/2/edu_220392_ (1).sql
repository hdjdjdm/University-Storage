-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Хост: 10.0.7.170
-- Время создания: Сен 29 2023 г., 12:47
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
-- Структура таблицы `Products`
--

CREATE TABLE `Products` (
  `Id` int NOT NULL,
  `Название` varchar(100) NOT NULL,
  `Калории` int NOT NULL,
  `user_id` int NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Дамп данных таблицы `Products`
--

INSERT INTO `Products` (`Id`, `Название`, `Калории`, `user_id`) VALUES
(1, 'Яйцо куриное', 157, 1),
(2, 'Баклажан', 24, 1),
(3, 'Кабачок', 24, 1),
(4, 'Томат (помидор)', 20, 1),
(5, 'Молоко 1,5%', 45, 1),
(6, 'Сыр \"Пармезан\"', 392, 1),
(7, 'Оладьи', 213, 1),
(8, 'Арахис', 552, 1),
(9, 'Морковь', 35, 1),
(10, 'Огурец', 14, 1),
(11, 'Тыква', 22, 1),
(12, 'Банан		', 96, 1),
(13, 'Колбаски охотничьи', 463, 1),
(14, 'Яблоки', 47, 1),
(15, 'Гематоген', 354, 1);

-- --------------------------------------------------------

--
-- Структура таблицы `Users`
--

CREATE TABLE `Users` (
  `user_id` int NOT NULL,
  `Пароль` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `Почта` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `Вес` int NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Дамп данных таблицы `Users`
--

INSERT INTO `Users` (`user_id`, `Пароль`, `Почта`, `Вес`) VALUES
(1, '123456', 'adsdassa@mail.ru', 66),
(2, '134135', 'feeq@gmail.com', 57),
(3, '351531', 'qwqwwq@mail.ru', 74),
(4, '146461fw', '315351@list.ru', 53),
(5, '1546461', 'htekt@gmail.com', 88),
(6, '246tgrw24', 'gaeae@mail.ru', 64),
(7, 'aruhraar45', '13rf13@gmail.com', 86);

--
-- Индексы сохранённых таблиц
--

--
-- Индексы таблицы `Products`
--
ALTER TABLE `Products`
  ADD PRIMARY KEY (`Id`),
  ADD KEY `user_id` (`user_id`);

--
-- Индексы таблицы `Users`
--
ALTER TABLE `Users`
  ADD PRIMARY KEY (`user_id`),
  ADD UNIQUE KEY `user_id` (`user_id`);

--
-- Ограничения внешнего ключа сохраненных таблиц
--

--
-- Ограничения внешнего ключа таблицы `Products`
--
ALTER TABLE `Products`
  ADD CONSTRAINT `Products_ibfk_1` FOREIGN KEY (`user_id`) REFERENCES `Users` (`user_id`) ON DELETE RESTRICT ON UPDATE RESTRICT;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
