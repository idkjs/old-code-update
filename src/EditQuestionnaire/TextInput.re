open Utils;

[@react.component]
let make = (~label, ~value, ~onChange, ()) =>
  <label>
    {s(label)}
    <br />
    <input
      type_="text"
      value
      onChange={event => onChange(ReactEvent.Form.target(event)##value)}
    />
  </label>;
