pipeline {
    agent { docker { image 'ubuntu:16.04' } }
    
    stages {
        stage('Build') {
            step {
                sh '''
                apt-get update
                apt-get -y install ranger
                gcc --version
                '''
            }
            step {
                sh 'echo "I am done building stuff"'
            }
        }
        stage('UnitTests') {
            step {
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