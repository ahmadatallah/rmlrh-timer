[%raw {| require('../styles/Button.css') |}]

type categoryT =
   | SECONDARY
   | PRIMARY;
 
let classNameOfCategory = category =>
   "Button "
   ++ (
     switch (category) {
     | SECONDARY => "secondary"
     | PRIMARY => "primary"
     }
    );
 
[@react.component]
  let make = (
     ~onClick, 
     ~title: string,
     ~children: string,
     ~disabled: bool=false,
     ~category: categoryT=SECONDARY,
     ~type_="button",
     ) => {
    <button onClick title className={category |> classNameOfCategory} disabled>
      { children |> ReasonReact.string }
    </button>;
  };                 