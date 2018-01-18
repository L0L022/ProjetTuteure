CREATE TABLE Form(
id_form INTEGER PRIMARY KEY,
name TEXT NOT NULL,
description TEXT NOT NULL,
creation_date DATE NOT NULL,
modification_date DATE NOT NULL
);

CREATE TABLE Subject(
id_subject INTEGER PRIMARY KEY,
id_form INTEGER,
modification_date DATE NOT NULL,
valid BOOL NOT NULL,
FOREIGN KEY () REFERENCES Form(id_form)
);;

CREATE TABLE Reply(
id_reply INTEGER PRIMARY KEY,
id_subject INTEGER,
id_question INTEGER,
modification_date DATE NOT NULL,
FOREIGN KEY (id_subject) REFERENCES Subject(id_subject),
FOREIGN KEY (id_question) REFERENCES Question(id_question)
);

CREATE TABLE OpenedReply(
id_reply INTEGER PRIMARY KEY,
modification_date DATE NOT NULL,
word TEXT NOT NULL;
FOREIGN KEY (id_reply) REFERENCES Reply(id_reply),
);

CREATE TABLE ClosedReply(
id_reply INTEGER PRIMARY KEY,
id_choice INTEGER
modification_date DATE NOT NULL,
FOREIGN KEY (id_reply) REFERENCES Reply(id_reply),
FOREIGN KEY (id_choice) REFERENCES Choice(id_choice),
);

CREATE TABLE Question(
id_question INTEGER PRIMARY KEY,
id_form INTEGER,
modification_date DATE NOT NULL,
FOREIGN KEY (id_form) REFERENCES Form(id_form)
);

CREATE TABLE ClosedQuestion(
id_question INTEGER PRIMARY KEY,
modification_date DATE NOT NULL,
question_type TEXT NOT NULL,
FOREIGN KEY (id_question) REFERENCES Question(id_question)
);

CREATE TABLE OpenedQuestion(
id_question INTEGER PRIMARY KEY,
modification_date DATE NOT NULL,
nb_word INTEGER NOT NULL,
FOREIGN KEY (id_question) REFERENCES Question(id_question)
);

CREATE TABLE Choice(
id_choice INTEGER PRIMARY KEY,
id_question INTEGER,
modification_date DATE NOT NULL,
meaning TEXT NOT NULL,
FOREIGN KEY (id_question) REFERENCES Question(id_question)
);

CREATE TABLE Subsituent_Term(
id_substituent_term INTEGER PRIMARY KEY,
modification_date DATE NOT NULL,
word TEXT NOT NULL
);

CREATE TABLE Substituted_Term(
id_substituent_term INTEGER,
word TEXT NOT NULL,
PRIMARY KEY (id_substituent_term, word),
FOREIGN KEY (id_substituent_term) REFERENCES Subsituent_Term(id_substituent_term)
);

2h31