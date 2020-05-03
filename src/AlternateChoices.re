open Utils;

[@react.component]
let make = (~description, ~questions, ~id, ~value, ~onChange, ()) =>
  ReactCompat.useRecordApi({
    ...ReactCompat.component,

    render: _self =>
      <>
        <h2> {s(description)} </h2>
        {questions
         |> mapi((index, question) =>
              <label key={string_of_int(index)} className=Styles.choice>
                <input
                  type_="radio"
                  name={"question" ++ string_of_int(id)}
                  value=question
                  checked={Answer.contains(value, question)}
                  onChange={Answer.fromInput |- onChange}
                />
                {s(question)}
              </label>
            )}
      </>,
  });
