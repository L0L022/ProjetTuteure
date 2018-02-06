INSERT INTO T_FORM_FRM VALUES
(1, 'Formulaire 1', 'Description du premier formulaire.', 0, 0),
(2, 'Formulaire 2', 'Description du second formulaire.', 0, 0);

INSERT INTO T_QUESTION_QST VALUES
(1, 1, 'opened', 'Question 1 ouverte', 10, 0),
(2, 1, 'unique', 'Question 2 unique', 0, 0),
(3, 1, 'multiple', 'Question 3 multiple', 0, 0),
(4, 1, 'opened', 'Question 4 ouverte', 4, 0),
(5, 1, 'unique', 'Question 5 unique', 0, 0),
(6, 1, 'multiple', 'Quesiton 6 multiple', 0, 0),
(7, 2, 'opened', 'Question 7 ouverte', 15, 0),
(8, 2, 'unique', 'Question 8 unique', 0, 0);

INSERT INTO T_CHOICE_CHC VALUES
(1, 2, 0, 'Choix 1'),
(2, 2, 0, 'Choix 2'),
(3, 2, 0, 'Choix 3'),
(4, 3, 0, 'Choix 4'),
(5, 3, 0, 'Choix 5'),
(6, 3, 0, 'Choix 6'),
(7, 5, 0, 'Choix 7'),
(8, 5, 0, 'Choix 8'),
(9, 6, 0, 'Choix 9'),
(10, 6, 0, 'Choix 10'),
(11, 8, 0, 'Choix 11'),
(12, 8, 0, 'Choix 12');

INSERT INTO T_SUBJECT_SBJ VALUES
(1, 1, 0, 0),
(2, 1, 0, 1),
(3, 1, 0, 1),
(4, 2, 0, 0),
(5, 2, 0, 1);

INSERT INTO TJ_SBJ_QST VALUES
(1, 1, 0, ''),
(1, 4, 0, ''),
(2, 1, 0, ''),
(2, 4, 0, ''),
(3, 1, 0, ''),
(3, 4, 0, ''),
(4, 7, 0, ''),
(5, 7, 0, '');

INSERT INTO TJ_SBJ_CHC VALUES
(1, 2, 0),
(1, 4, 0),
(1, 5, 0),
(1, 7, 0),
(1, 9, 0),
(1, 10, 0),
(2, 1, 0),
(2, 6, 0),
(2, 7, 0),
(2, 9, 0),
(3, 3, 0),
(3, 4, 0),
(3, 5, 0),
(3, 6, 0),
(3, 8, 0),
(3, 9, 0),
(3, 10, 0),
(4, 11, 0),
(5, 12, 0);
