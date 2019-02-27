pipeline {
    agent { dockerfile true }
    
    stages {
        stage('Build') {
            steps {
                sh '''
                apt-get update
                apt-get -y install ranger
                gcc --version
                '''
                sh 'echo "I am done building stuff"'
            }
        }
        stage('UnitTests') {
            steps {
                sh 'echo "I am now testing stuff"'
            }
        }
    }
    post {
        always {
            sh 'echo "do cleanup"'
        }
    }
}