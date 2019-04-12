declare module "node-windpapi" {
    declare function protect(
        userData: Uint8Array,
        optionalEntropy: Uint8Array,
        scope: "CurrentUser" | "LocalMachine"
    ): Uint8Array;

    declare function unprotect(
        encryptedData: Uint8Array,
        optionalEntropy: Uint8Array,
        scope: "CurrentUser" | "LocalMachine"
    ): Uint8Array;
}
