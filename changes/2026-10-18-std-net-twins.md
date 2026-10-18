- **`std:net`: one scope function per resource (ADR-0048 row 8, freeze C3).** `withListen`, `withConnect`, `withListener`,
  `withListenerNet`, `withAccepted`, `serveAccepted`, `spawnAccepted`, `withConnection`, `withConnectionUntil` and
  `withConnectionBeside` take a body that returns any `T`, `void` included. The twins `useListen`, `useConnect`,
  `useListener`, `useListenerNet`, `useAccepted`, `serveAcceptedDo`, `spawnAcceptedDo`, `useConnection`,
  `useConnectionUntil` and `useConnectionBeside` stay one release as `@Deprecated` wrappers (W0440) with unchanged
  signatures; examples, tests, tutorial and docs use the `with*` names.
