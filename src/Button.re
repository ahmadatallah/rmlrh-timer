module Styles = {
  /* Open the Css module, so we can access the style properties below without prefixing them with Css. */
  open Css;

  let button = style([
    padding(px(6)),
    margin(px(6)),
    fontSize(rem(1.0)),
    borderRadius(px(5)),
    boxShadow(~y=px(1), ~blur=px(5), rgba(0,0,0,0.2))
  ]);
  
  let primary = style([
    color(white),
    backgroundColor(rgb(32, 148, 243))
  ]);

  let secondary = style([
    color(black),
    backgroundColor(rgb(224, 224, 224))
  ]);

  let disabled = style([
    color(rgba(0, 0, 0, 0.26)),
    backgroundColor(rgba(0, 0, 0, 0.12))
  ]);
};

type categoryT =
   | SECONDARY
   | PRIMARY;
 
let classNameOfCategory = (category) => {
  let buttonCategory = switch (category) {
  | SECONDARY => Styles.secondary
  | PRIMARY => Styles.primary
  };
  Css.(merge([Styles.button, buttonCategory]));
};

[@react.component]
  let make = (
     ~onClick, 
     ~title: string,
     ~children: string,
     ~category: categoryT=SECONDARY,
     ~type_="button",
     ) => {
    <button onClick title className={category |> classNameOfCategory}>
      { children |> ReasonReact.string }
    </button>;
  };                 