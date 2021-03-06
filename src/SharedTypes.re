type id = string;
type description = string;
type choice = string;

type question =
  | TextField(description)
  | TextArea(description)
  | AlternateChoices(description, list(choice))
  | MultipleChoices(description, list(choice));

type questionnaire = {
  description,
  questions: list(question),
  userId: id,
};

type person = {
  name: string,
  age: int,
};
