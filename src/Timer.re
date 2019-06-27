type state = { 
   seconds: int, 
   isTicking: bool
};

type action = 
  | Start 
  | Stop
  | Reset 
  | Tick;

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

   React.useEffect(() => {
      let timer = Js.Global.setInterval(() => dispatch(Tick), 1000);
      // return of callback-function => cleanup 
      Some(() => Js.Global.clearInterval(timer));
   });
   
   <div>
    { ReasonReact.string(
        "Timer: " ++ string_of_int(state.seconds),
    )}
   </div>
};