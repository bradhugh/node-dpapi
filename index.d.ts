declare module "node-windpapi" {
    function protect(
        userData: Uint8Array,
        optionalEntropy: Uint8Array,
        scope: "CurrentUser" | "LocalMachine"
    ): Uint8Array;

    function unprotect(
        encryptedData: Uint8Array,
        optionalEntropy: Uint8Array,
        scope: "CurrentUser" | "LocalMachine"
    ): Uint8Array;
}
