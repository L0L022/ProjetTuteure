CREATE TABLE Formulaire(
id_formulaire INTEGER PRIMARY KEY,
nom TEXT NOT NULL,
description TEXT NOT NULL,
date_création DATE NOT NULL,
date_modification DATE NOT NULL
);

CREATE TABLE Sujet(
id_sujet INTEGER PRIMARY KEY,
id_formulaire INTEGER,
date_modification DATE NOT NULL,
validé BOOL NOT NULL,
FOREIGN KEY (id_formulaire) REFERENCES Formulaire(id_formulaire)
);;

CREATE TABLE Réponse(
id_réponse INTEGER PRIMARY KEY,
id_sujet INTEGER,
id_question INTEGER,
date_modification DATE NOT NULL,
mots TEXT NOT NULL,
FOREIGN KEY (id_sujet) REFERENCES Sujet(id_sujet),
FOREIGN KEY (id_question) REFERENCES Question(id_question)
);

CREATE TABLE Question(
id_question INTEGER PRIMARY KEY,
id_formulaire INTEGER,
date_modification DATE NOT NULL,
intitulé TEXT NOT NULL,
type_question TEXT NOT NULL,
nb_mots INTEGER NOT NULL,
FOREIGN KEY (id_formulaire) REFERENCES Formulaire(id_formulaire)
);

CREATE TABLE Choix(
id_choix INTEGER PRIMARY KEY,
id_question INTEGER,
date_modification DATE NOT NULL,
signification TEXT NOT NULL,
FOREIGN KEY (id_question) REFERENCES Question(id_question)
);

CREATE TABLE RéponseChoix(
id_réponse INTEGER,
id_choix INTEGER,
PRIMARY KEY (id_réponse, id_choix),
FOREIGN KEY (id_réponse) REFERENCES Réponse(id_réponse),
FOREIGN KEY (id_choix) REFERENCES Choix(id_choix)
);

CREATE TABLE Terme_subtituant(
id_terme_subtituant INTEGER PRIMARY KEY,
date_modification DATE NOT NULL,
mot TEXT NOT NULL
);

CREATE TABLE Terme_subtitué(
id_terme_subtituant INTEGER,
mot TEXT NOT NULL,
PRIMARY KEY (id_terme_subtituant, mot),
FOREIGN KEY (id_terme_subtituant) REFERENCES Terme_subtituant(id_terme_subtituant)
);

1h51