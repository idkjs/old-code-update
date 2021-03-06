open Utils;

module Component = {
  [@bs.send]
  external onAuthStateChanged:
    (Firebase.auth, Js.Nullable.t(Firebase.user) => unit) => unit =
    "onAuthStateChanged";

  type state =
    | Loading
    | Authenticated(Firebase.user)
    | Unauthenticated;
  type action =
    | SetUser(Js.Nullable.t(Firebase.user));

  [@react.component]
  let make = (~context: AppContext.context, ~children, ()) => {
    let children = React.Children.toArray(children);
    ReactCompat.useRecordApi({
        ...ReactCompat.component,


      initialState: () => Loading,
      didMount: ({send}) =>
        context.firebase
        ->Firebase.auth
        ->onAuthStateChanged(user => send(SetUser(user))),
      reducer: (action: action, _state: state) =>
        switch (action) {
        | SetUser(user) =>
          switch (Js.Nullable.toOption(user)) {
          | None => Update(Unauthenticated)
          | Some(user) => Update(Authenticated(user))
          }
        },
      render: ({state}) =>
        switch (state) {
        | Loading => <h1> {s("Loading...")} </h1>
        | Unauthenticated => <FirebaseAuth />
        | Authenticated(_) => children |> ReasonReact.array
        },
    });
  };
};

[@react.component]
let make = (~children, ()) => {
  let children = React.Children.toArray(children);
  ReactCompat.useRecordApi({
    ...component,

    render: _self =>
      <AppContext.Consumer>
        ...{context => <Component context> ...children </Component>}
      </AppContext.Consumer>,
  });
};
