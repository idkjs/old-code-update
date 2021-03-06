open Utils;
open SharedTypes;

module Component = {
  /* TODO: Refactor this duplicated function from SelectQuestionType */
  let getDescription =
    fun
    | TextField(description)
    | TextArea(description)
    | AlternateChoices(description, _)
    | MultipleChoices(description, _) => description;

  [@react.component]
  let make = (~questionnaire, ~answers: list(AnswerDB.t), ()) =>
    ReactCompat.useRecordApi({
      ...ReactCompat.component,

      render: _self =>
        <>
          <h1> {s("Answers for: " ++ questionnaire.description)} </h1>
          <table className={Styles.table ++ " " ++ Styles.textCenter}>
            <thead>
              <tr>
                {questionnaire.questions
                 |> mapi((index, question) =>
                      <th key={string_of_int(index)}>
                        {question |> getDescription |> s}
                      </th>
                    )}
              </tr>
            </thead>
            <tbody>
              {answers
               |> mapi((index, answer) =>
                    <tr key={string_of_int(index)}>
                      {answer
                       |> Array.mapi((index, a) =>
                            <td key={string_of_int(index)}>
                              {a
                               |> Answer.elements
                               |> Array.of_list
                               |> Js.Array.joinWith(", ")
                               |> s}
                            </td>
                          )
                       |> ReasonReact.array}
                    </tr>
                  )}
            </tbody>
          </table>
        </>,
    });
};

module Loader = {
  type state =
    | Loading
    | Loaded(questionnaire, list(AnswerDB.t));
  type action =
    | Loaded(questionnaire, list(AnswerDB.t))
    | NewAnswer(AnswerDB.t);

  [@react.component]
  let make = (~id, ~context: AppContext.context, ()) => {
    let answerDB =
      AnswerDB.make(context.firebaseInstance, ~transformPath=path =>
        path ++ "/" ++ id ++ "/answers"
      );
    ReactCompat.useRecordApi({
      ...ReactCompat.component,

      initialState: () => Loading,
      didMount: ({send, onUnmount}) => {
        context.questionnaireDB.get(
          id,
          questionnaire => {
            send(Loaded(questionnaire, []));
            let unsubscribe =
              answerDB.onAdded(answer => send(NewAnswer(answer)));
            onUnmount(unsubscribe |- ignore);
          },
        )
        |> ignore;
      },
      reducer: (action: action, state: state) =>
        switch (action) {
        | Loaded(questionnaire, answers) =>
          ReactCompat.Update(Loaded(questionnaire, answers))
        | NewAnswer(answer) =>
          switch (state) {
          | Loading => ReactCompat.NoUpdate
          | Loaded(questionnaire, answers) =>
            ReactCompat.Update(
              Loaded(questionnaire, answers |> List.append([answer])),
            )
          }
        },
      render: ({state}) =>
        switch (state) {
        | Loading => <h1> {s("Loading...")} </h1>
        | Loaded(questionnaire, answers) =>
          <Component questionnaire answers />
        },
    });
  };
};

[@react.component]
let make = (~id, ()) =>
  ReactCompat.useRecordApi({
    ...ReactCompat.component,

    render: _self =>
      <AppContext.Consumer>
        ...{context => <Loader id context />}
      </AppContext.Consumer>,
  });
