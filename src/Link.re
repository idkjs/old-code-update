[@react.component]
let make = (~href: string, ~className="", ~children, ()) => {
  let children = React.Children.toArray(children);
  ReactCompat.useRecordApi({
    ...ReactCompat.component,

    render: _self =>
      <a
        href
        className
        onClick={ev => {
          ReactEvent.Synthetic.preventDefault(ev);
          ReasonReact.Router.push(href);
        }}>
        {children |> ReasonReact.array}
      </a>,
  });
};
