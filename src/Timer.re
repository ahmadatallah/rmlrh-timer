module Styles = {
   /* Open the Css module, so we can access the style properties below without prefixing them with Css. */
   open Css;

   let timer = style([
      border(px(1), solid, black),
      borderRadius(px(8)),
      maxWidth(px(180)),
      textAlign(center)
   ]);

   let seconds = style([
      color(hex("444444")), 
      fontSize(px(42)),
      margin(px(16))
   ]);


};

type state = { 
   seconds: int, 
   isTicking: bool
};

type action = 
  | Start 
  | Stop
  | Reset 
  | Tick;

let padNumber = numString =>
  if (numString |> int_of_string < 10) {
    "0" ++ numString;
  } else {
    numString;
  };

let formatTime = seconds => {
  let mins = seconds / 60;
  let minsString = mins |> string_of_int |> padNumber;
  let seconds = seconds mod 60;
  let secondsString = seconds |> string_of_int |> padNumber;
  minsString ++ ":" ++ secondsString;
};

[@react.component]
let make = () => {
   let initialState = { 
       isTicking: false,
       seconds: 30
   };
   let (state, dispatch) =  React.useReducer(
       (state, action) => 
          switch action {
          | Start => { ...state, isTicking: true }
          | Stop => { ...state, isTicking: false }
          | Reset => { ...state, seconds: 30 }
          | Tick => state.isTicking && state.seconds > 0
            ? {...state, seconds: state.seconds - 1} : state
          },
          initialState,
   );
   let dispatchStart = _event => dispatch(Start);
   let dispatchStop = _event => dispatch(Stop);
   let dispatchReset = _event => dispatch(Reset);


   React.useEffect(() => {
      let timer = Js.Global.setInterval(() => dispatch(Tick), 1000);
      // return of callback-function => cleanup 
      Some(() => Js.Global.clearInterval(timer));
   });
   
   <div className=Styles.timer>
    <p className=Styles.seconds>
      {state.seconds |> formatTime |> ReasonReact.string}
    </p>
    {state.isTicking
        ? <Button
            onClick=dispatchStop
            title="STOP"
            category=Button.PRIMARY>
            "Stop"
         </Button>
        : <>
            <Button  
               onClick=dispatchStart
               title="START"
               category=Button.SECONDARY>
               "Start"
            </Button>
            <Button 
               onClick=dispatchReset
               title="RESET"
               category=Button.SECONDARY>
               "Reset"
            </Button>

          </>
    }
   </div>
};