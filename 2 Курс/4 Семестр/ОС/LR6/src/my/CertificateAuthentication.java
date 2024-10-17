package my;

import java.io.FileInputStream;
import java.security.KeyStore;
import java.security.Security;
import java.security.cert.Certificate;
import java.security.cert.CertificateFactory;
import java.security.cert.X509Certificate;
import org.bouncycastle.jce.provider.BouncyCastleProvider;
public class CertificateAuthentication {
    public static boolean authenticate(String certificateFile, String keystoreFile, String keystorePassword) throws Exception {
        Security.addProvider(new BouncyCastleProvider());
        FileInputStream inputStream = new FileInputStream(certificateFile);
        Certificate certificate = CertificateFactory.getInstance("X.509", "BC").generateCertificate(inputStream);

        // Загружаем хранилище ключей, которое содержит сертификаты удостоверяющих центров
        KeyStore keystore = KeyStore.getInstance("PKCS12");
        keystore.load(new FileInputStream(keystoreFile), keystorePassword.toCharArray());

        // Проверяем, что сертификат действителен и подписан доверенным удостоверяющим центром
        X509Certificate x509Certificate = (X509Certificate) certificate;
        x509Certificate.checkValidity();
        try{
            x509Certificate.verify(certificate.getPublicKey());
            return true;
        } catch (Exception ex){
            System.out.println(ex.getMessage());
            return false;
        }
    }
}
