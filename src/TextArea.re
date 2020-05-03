open Utils;

[@react.component]
let make = (~description, ~value, ~onChange, ()) =>
  ReactCompat.useRecordApi({
    ...ReactCompat.component,

    render: _self =>
      <>
        <h2> {s(description)} </h2>
        <textarea
          value={Answer.get(value)}
          onChange={Answer.fromInput |- onChange}
        />
      </>,
  });
